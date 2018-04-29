/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <sstream>

#if defined(_MSC_VER)
#include <io.h>
#elif defined(__linux) || defined(__linux__)
#include <sys/types.h>
#include <dirent.h>
#endif

//名单中最大学生数量
#define MAX_STUDENT_NUM 12

using namespace std;

//学生信息结构体
struct Student
{
	char no[10];
	char name[10];

	//课程名单中班级的两种形式: 一班/1班
	char class_1[10];
	char class_2[10];

	//检查的结果
	bool hand_in;
	bool no_check;
	bool name_check;
	bool class_check;
	int info_num_check; //1表示信息完整，0表示信息不全，-1表示信息过多
	bool line_read_success; //是否取到首行信息
	bool pass;
};

struct List
{
	int student_num;
	Student student_info[MAX_STUDENT_NUM];
};

int annotation_end(char *str);
bool check_class(char *, char *, char *);
void check_first_line(char(*first_line_info)[20], char(*to_be_check)[20], Student &student);
void check_info_match(char(*to_be_check)[20], Student &student);
void print_result(Student &student, char *filename);
void student_stat_init(Student &student);
bool check_file_extension(char *);
void read_check(char *file_path, char *filename, Student &student);

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cout << "参数数量不足" << endl;
		return -1;
	}

	if (strcmp(argv[1], "-checktitle"))
	{
		cout << "功能参数错误" << endl;
		return -1;
	}

	/********首先从dat文件中读取指定课程的所有学生信息********/

	//读取信息的文件
	ifstream infile;

#if defined(_MSC_VER)
	char listname[50] = "source\\";
#elif defined(__linux) || defined(__linux__)
	char listname[50] = "source/";
#endif 

	strcat(listname, argv[2]);
	strcat(listname, ".dat");

	infile.open(listname, ios::in);

	if (!infile.is_open())
	{
		cout << "无法打开课程名单，请确认source文件夹路径是否正确" << endl;
		return -1;
	}

	//从文件中逐行读取学生个人信息
	List new_list;
	new_list.student_num = 0;
	while (!infile.eof())
	{
		infile >> new_list.student_info[new_list.student_num].no;
		infile >> new_list.student_info[new_list.student_num].name;
		infile >> new_list.student_info[new_list.student_num].class_1;
		infile >> new_list.student_info[new_list.student_num].class_2;

		new_list.student_num++;
	}

	//命令行参数中提供指定文件名的检查
	if (strcmp(argv[3], "all"))
	{
		//检查用户提供的文件名后缀是否符合要求
		if (!check_file_extension(argv[3]))
		{
			cout << "不是源程序文件" << endl;
			return 0;
		}

		//逐个打开学生名单中对应的学生文件夹并检查
		for (int i = 0; i < new_list.student_num; i++)
		{
			student_stat_init(new_list.student_info[i]);

			char to_be_check[3][20];
			//文件路径（初始为source）
			char path[260] = "source";

#if defined(_MSC_VER)
			strcat(path, "\\");
			strcat(path, argv[2]);
			strcat(path, "-");
			strcat(path, new_list.student_info[i].no);
			strcat(path, "\\");
			strcat(path, argv[3]);
#elif defined(__linux) || defined(__linux__)
			strcat(path, "/");
			strcat(path, argv[2]);
			strcat(path, "-");
			strcat(path, new_list.student_info[i].no);
			strcat(path, "/");
			strcat(path, argv[3]);
#endif
			read_check(path, argv[3], new_list.student_info[i]);
		}
	}
	else
	{
		//命令行参数提供"all"，即需要检查所有文件
		//交了什么文件就检查什么文件，未提交的就不管了

#if defined(_MSC_VER)		
		_finddata_t file;
		intptr_t k;
		intptr_t HANDLE; //记录第一次打开的文件句柄，关闭时需用此值
#elif defined(__linux) || defined(__linux__)
		DIR            *dir;
		struct dirent  *node;
#endif 

		for (int i = 0; i < new_list.student_num; i++)
		{
#if defined(_MSC_VER)
			//文件路径（初始为source）
			char search_path[3][260] = { "source","source","source" };

			for (int j = 0; j < 3; j++)
			{
				strcat(search_path[j], "\\");
				strcat(search_path[j], argv[2]);
				strcat(search_path[j], "-");
				strcat(search_path[j], new_list.student_info[i].no);
				strcat(search_path[j], "\\");

				switch (j)
				{
				case 0:strcat(search_path[j], "*.cpp"); break;
				case 1:strcat(search_path[j], "*.c"); break;
				case 2:strcat(search_path[j], "*.h"); break;
				}

				k = HANDLE = _findfirst(search_path[j], &file);
				while (k != -1)
				{
					student_stat_init(new_list.student_info[i]);

					char file_path[260] = "source";

					strcat(file_path, "\\");
					strcat(file_path, argv[2]);
					strcat(file_path, "-");
					strcat(file_path, new_list.student_info[i].no);
					strcat(file_path, "\\");
					strcat(file_path, file.name);

					read_check(file_path, file.name, new_list.student_info[i]);

					k = _findnext(HANDLE, &file);
				}
				_findclose(HANDLE);
			}

#elif defined(__linux) || defined(__linux__)
			char search_path[260] = "source";

			strcat(search_path, "/");
			strcat(search_path, argv[2]);
			strcat(search_path, "-");
			strcat(search_path, new_list.student_info[i].no);

			if ((dir = opendir(search_path)) == NULL)
			{
				//若这个人未提交则不要管他了
				continue;
			}

			/* 循环扫描该目录下的所有文件 */
			while ((node = readdir(dir)) != NULL)
			{
				student_stat_init(new_list.student_info[i]);

				if (check_file_extension(node->d_name))
				{
					char file_path[260] = "source";

					strcat(file_path, "/");
					strcat(file_path, argv[2]);
					strcat(file_path, "-");
					strcat(file_path, new_list.student_info[i].no);
					strcat(file_path, "/");
					strcat(file_path, node->d_name);

					read_check(file_path, node->d_name, new_list.student_info[i]);
				}

			}

			closedir(dir);
#endif 
		}
	}

	infile.close();
	return 0;
}

//该函数检查用户在命令行参数中提供的文件名后缀是否符合要求
bool check_file_extension(char *filename)
{
	bool match = 0;
	if (strcmp(filename + strlen(filename) - 4, ".cpp") == 0)
	{
		match = 1;
	}
	else if (strcmp(filename + strlen(filename) - 2, ".c") == 0)
	{
		match = 1;
	}
	else if (strcmp(filename + strlen(filename) - 2, ".h") == 0)
	{
		match = 1;
	}

	return match;
}

//该函数用于判断一段字符串中是否含有"*/"
int annotation_end(char *str)
{
	//其实就是看一个字符串是否含有*/，并且看*/是作为单独字符串存在还是结合在字符串尾部
	if (strcmp(str, "*/") == 0)
		return 1;
	else if (str[strlen(str) - 1] == '/' && str[strlen(str) - 2] == '*')
		return -1;
	else return 0;
}

//该函数用于检查某段字符串是否与班级匹配
bool check_class(char *class_0, char *class_1, char *class_2)
{
	bool match = 0;

	//首先先取待检查字符串的最后四个字节,例如计算机二班
	char to_be_check[20];
	strcpy(to_be_check, class_0 + strlen(class_0) - 4);

	if (strcmp(to_be_check, class_1) == 0)
	{
		match = 1;
	}
	else if (strcmp(to_be_check, class_2) == 0)
	{
		match = 1;
	}

	//尝试取最后三个字节，例如计算机2班
	strcpy(to_be_check, class_0 + strlen(class_0) - 3);

	if (strcmp(to_be_check, class_1) == 0)
	{
		match = 1;
	}
	else if (strcmp(to_be_check, class_2) == 0)
	{
		match = 1;
	}

	//然后还要考虑数强和数理强化班这种奇葩的情况
	if (strncmp(class_0, class_1, 4) == 0 || strncmp(class_0, class_2, 4) == 0)
	{
		match = 1;
	}
	else if (strncmp(class_0, class_1, 8) == 0 || strncmp(class_0, class_2, 8) == 0)
	{
		match = 1;
	}

	return match;
}

/********检查是否成功读取到首行信息  以及信息项是否缺失或多余********/
void check_first_line(char(*first_line_info)[20], char(*to_be_check)[20], Student &student)
{
	/********检查是否成功读取到首行信息  以及信息项是否缺失或多余********/
	if (strcmp(first_line_info[0], "//") == 0)
	{
		//在第一段字符串为//的情况下，只可能有四段字符串
		if (first_line_info[4][0] != 0)
		{
			student.info_num_check = -1;
		}
		else if (first_line_info[3][0] == 0)
		{
			student.info_num_check = 0;
		}
		else
		{
			student.info_num_check = 1;
			strcpy(to_be_check[0], first_line_info[1]);
			strcpy(to_be_check[1], first_line_info[2]);
			strcpy(to_be_check[2], first_line_info[3]);
		}
	}
	else if (strncmp(first_line_info[0], "//", 2) == 0)
	{
		if (first_line_info[3][0] != 0)
		{
			student.info_num_check = -1;
		}
		else if (first_line_info[2][0] == 0)
		{
			student.info_num_check = 0;
		}
		else
		{
			student.info_num_check = 1;
			strcpy(to_be_check[0], first_line_info[0] + 2);
			strcpy(to_be_check[1], first_line_info[1]);
			strcpy(to_be_check[2], first_line_info[2]);
		}
	}
	else if (strcmp(first_line_info[0], "/*") == 0)
	{
		bool end_exist = 0;
		int end_pos;
		for (end_pos = 0; end_pos < 6; end_pos++)
		{
			if (annotation_end(first_line_info[end_pos]) == 1)
			{
				end_exist = 1;
				if (end_pos < 4) student.info_num_check = 0;
				else if (end_pos>4) student.info_num_check = -1;
				else student.info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[1]);
				strcpy(to_be_check[1], first_line_info[2]);
				strcpy(to_be_check[2], first_line_info[3]);

				break;
			}

			else if (annotation_end(first_line_info[end_pos]) == -1)
			{
				end_exist = 1;
				if (end_pos < 3) student.info_num_check = 0;
				else if (end_pos>3) student.info_num_check = -1;
				else student.info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[1]);
				strcpy(to_be_check[1], first_line_info[2]);
				strcpy(to_be_check[2], first_line_info[3]);
				to_be_check[2][strlen(first_line_info[3]) - 2] = '\0';

				break;
			}
		}
		if (!end_exist) student.line_read_success = 0;
	}
	else if (strncmp(first_line_info[0], "/*", 2) == 0)
	{
		bool end_exist = 0;
		int end_pos;
		for (end_pos = 0; end_pos < 6; end_pos++)
		{
			if (annotation_end(first_line_info[end_pos]) == 1)
			{
				end_exist = 1;
				if (end_pos < 3) student.info_num_check = 0;
				else if (end_pos>3) student.info_num_check = -1;
				else student.info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[0] + 2);
				strcpy(to_be_check[1], first_line_info[1]);
				strcpy(to_be_check[2], first_line_info[2]);
				break;
			}

			else if (annotation_end(first_line_info[end_pos]) == -1)
			{
				end_exist = 1;
				if (end_pos < 2) student.info_num_check = 0;
				else if (end_pos>2) student.info_num_check = -1;
				else student.info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[0] + 2);
				strcpy(to_be_check[1], first_line_info[1]);
				strcpy(to_be_check[2], first_line_info[2]);
				to_be_check[2][strlen(first_line_info[2]) - 2] = '\0';
				break;
			}
		}

		if (!end_exist) student.line_read_success = 0;
	}
	else student.line_read_success = 0;
}

/********检查首行信息是否匹配********/
void check_info_match(char(*to_be_check)[20], Student &student)
{
	if (student.line_read_success)
	{
		/********检查首行信息是否匹配********/
		if (student.info_num_check == 1)
		{
			//检查学号
			for (int j = 0; j < 3; j++)
			{
				if (strcmp(student.no, to_be_check[j]) == 0)
				{
					student.no_check = 1;
					break;
				}
			}

			//检查姓名
			for (int j = 0; j < 3; j++)
			{
				if (strcmp(student.name, to_be_check[j]) == 0)
				{
					student.name_check = 1;
					break;
				}
			}

			for (int j = 0; j < 3; j++)
			{
				if (check_class(to_be_check[j], student.class_1, student.class_2))
				{
					student.class_check = 1;
					break;
				}
			}
		}
	}
}

/********根据判定打印检查结果********/
void print_result(Student &student, char *filename)
{
	cout << student.no << ' ';
	cout << student.name << ' ';
	cout << filename << ':';

	if (!student.hand_in)
	{
		cout << "未提交" << endl;
		return;
	}
	if (!student.line_read_success)
	{
		cout << "未取到首行信息" << endl;
		return;
	}
	else if (student.info_num_check == 0)
	{
		cout << "首行信息不全" << endl;
		return;
	}
	else if (student.info_num_check == -1)
	{
		cout << "首行信息过多" << endl;
		return;
	}

	if (!student.no_check)
	{
		cout << "学号不匹配 ";
		student.pass = 0;
	}

	if (!student.name_check)
	{
		cout << "姓名不匹配 ";
		student.pass = 0;
	}

	if (!student.class_check)
	{
		cout << "班级不匹配 ";
		student.pass = 0;
	}

	if (student.pass)
	{
		cout << "通过";
	}
	cout << endl;
}

//学生个体作业检查情况的初始化
void student_stat_init(Student &student)
{
	student.hand_in = 0;
	student.no_check = 0;
	student.name_check = 0;
	student.class_check = 0;
	student.info_num_check = 0; //1表示信息完整，0表示信息不全，-1表示信息过多
	student.line_read_success = 1; //是否取到首行信息
	student.pass = 1;
}

//读取作业文件和检查的主体部分
void read_check(char *file_path, char *filename, Student &student)
{
	char to_be_check[3][20];
	ifstream check_file(file_path, ios::in);

	if (!check_file.is_open())
	{
		//文件打不开，则判定名单中该学生未交作业
		student.hand_in = 0;
	}
	else
	{
		//判定作业已提交
		student.hand_in = 1;

		//临时字符串数组存储所读的首行信息
		char first_line_info[6][20] = { 0 };

		//将文件首行内容读取至字符串流
		istringstream istr;
		char first_line[100];
		check_file >> first_line;
		check_file.getline((first_line + strlen(first_line)), 100, '\n');

		istr.str(first_line);

		//将字符串流中的信息输入到first_line_info字符串数组
		for (int j = 0; j < 6; j++)
		{
			istr >> first_line_info[j];
		}

		check_first_line(first_line_info, to_be_check, student);

		check_info_match(to_be_check, student);
	}

	print_result(student, filename);

	check_file.close();
}