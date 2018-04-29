/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_MSC_VER)
#include <io.h>
#elif defined(__linux) || defined(__linux__)
#include <sys/types.h>
#include <dirent.h>
#endif 

//名单中最大学生数量
#define MAX_STUDENT_NUM 12
#define MAX_LINE_CHAR_NUM 256 //一行中最大的字符数量

//寻找注释头尾函数的返回值标记
#define HEAD 1 //在字符串头部
#define END 2 //在字符串尾部
#define BETWEEN 3 //在字符串中间部分
#define FAIL 0 //不存在于字符串中

//学生信息结构体
typedef struct Student
{
	char no[10];
	char name[10];

	//课程名单中班级的两种形式: 一班/1班
	char class_1[10];
	char class_2[10];

	//检查的结果
	int hand_in;
	int no_check;
	int name_check;
	int class_check;
	int info_num_check; //1表示信息完整，0表示信息不全，-1表示信息过多
	int line_read_success; //是否取到首行信息
	int pass;

	int linecount; //作业文件的行数
	int meaningful_line;
	int annotation_line;
	int with_annotation_line;
	int valid_char_num;
	int valid_anno_char;
}Student;

typedef struct List
{
	int student_num;
	struct Student student_info[MAX_STUDENT_NUM];
}List;

/***************************函数原型********************************/
int annotation_end(char *str);
int check_class(char *, char *, char *);
void check_first_line(char(*first_line_info)[20], char(*to_be_check)[20], struct Student *student);
void check_info_match(char(*to_be_check)[20], struct Student *student);
void print_result(struct Student *student, char *filename);
void student_stat_init(struct Student *student);
int check_file_extension(char *);
void read_check(char *file_path, char *filename, struct Student *student);
void count_line(char *file_path, char *filename, Student *student);
void analyse_line(char *file_path, char *filename, Student *student);
void meaningful_line(char  *file_path, char *filename, Student *student);
int meaningful_char(char ch);
char *alltrim(char *buf);
void annotation_line(char *file_path, char *filename, Student *student);
int find_annotation(char *source, const char *target);
void with_annotation_line(char *file_path, char *filename, Student *student);
void valid_char_num(char *file_path, char *filename, Student *student);
void valid_anno_char(char *file_path, char *filename, Student *student);
/******************************************************************/

int main(int argc, char *argv[])
{
	int i, j;

	if (argc < 4)
	{
		printf("参数数量不足\n");
		return -1;
	}

	/********首先从dat文件中读取指定课程的所有学生信息********/

	//读取信息的文件
	FILE *infile;

#if defined(_MSC_VER)
	char listname[50] = "source\\";
#elif defined(__linux) || defined(__linux__)
	char listname[50] = "source/";
#endif 

	strcat(listname, argv[2]);
	strcat(listname, ".dat");

	infile = fopen(listname, "r");

	if (infile == NULL)
	{
		printf("未能读取到学生名单，请确认source文件夹的路径是否正确\n");
		return -1;
	}

	//从文件中逐行读取学生个人信息
	struct List new_list;
	new_list.student_num = 0;
	while (!feof(infile))
	{
		fscanf(infile, "%s", new_list.student_info[new_list.student_num].no);
		fscanf(infile, "%s", new_list.student_info[new_list.student_num].name);
		fscanf(infile, "%s", new_list.student_info[new_list.student_num].class_1);
		fscanf(infile, "%s", new_list.student_info[new_list.student_num].class_2);

		new_list.student_num++;
	}
	/****************所有学生信息读取完毕****************/

	if (strcmp(argv[3], "all"))
	{
		//检查用户提供的文件名后缀是否符合要求
		if (!check_file_extension(argv[3]))
		{
			printf("不是源程序文件\n");
			return 0;
		}

		//逐个打开学生名单中对应的学生文件夹并检查
		for (i = 0; i < new_list.student_num; i++)
		{
			student_stat_init(&new_list.student_info[i]);

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

			if (strcmp(argv[1], "-linecount") == 0)
			{
				count_line(path, argv[3], &new_list.student_info[i]);
			}
			else if (strcmp(argv[1], "-lineanalyse") == 0)
			{
				analyse_line(path, argv[3], &new_list.student_info[i]);
			}
			else if (strcmp(argv[1], "-checktitle") == 0)
			{
				read_check(path, argv[3], &new_list.student_info[i]);
			}
			else
			{
				printf("功能参数错误\n");
				return 0;
			}
		}
	}
	else
	{
		//命令行参数提供"all"，即需要检查所有文件
		//交了什么文件就检查什么文件，未提交的就不管了

#if defined(_MSC_VER)		
		struct _finddata_t file;
		intptr_t k;
		intptr_t HANDLE; //记录第一次打开的文件句柄，关闭时需用此值
#elif defined(__linux) || defined(__linux__)
		DIR            *dir;
		struct dirent  *node;
#endif 

		for (i = 0; i < new_list.student_num; i++)
		{
#if defined(_MSC_VER)
			//文件路径（初始为source）
			char search_path[3][260] = { "source","source","source" };

			for (j = 0; j < 3; j++)
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
					student_stat_init(&new_list.student_info[i]);

					char file_path[260] = "source";

					strcat(file_path, "\\");
					strcat(file_path, argv[2]);
					strcat(file_path, "-");
					strcat(file_path, new_list.student_info[i].no);
					strcat(file_path, "\\");
					strcat(file_path, file.name);

					if (strcmp(argv[1], "-linecount") == 0)
					{
						count_line(file_path, file.name, &new_list.student_info[i]);
					}
					else if (strcmp(argv[1], "-lineanalyse") == 0)
					{
						analyse_line(file_path, file.name, &new_list.student_info[i]);
					}
					else if (strcmp(argv[1], "-checktitle") == 0)
					{
						read_check(file_path, file.name, &new_list.student_info[i]);
					}
					else
					{
						printf("功能参数错误\n");
						return 0;
					}

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
				student_stat_init(&new_list.student_info[i]);

				if (check_file_extension(node->d_name))
				{
					char file_path[260] = "source";

					strcat(file_path, "/");
					strcat(file_path, argv[2]);
					strcat(file_path, "-");
					strcat(file_path, new_list.student_info[i].no);
					strcat(file_path, "/");
					strcat(file_path, node->d_name);

					if (strcmp(argv[1], "-linecount") == 0)
					{
						count_line(file_path, node->d_name, &new_list.student_info[i]);
					}
					else if (strcmp(argv[1], "-lineanalyse") == 0)
					{
						analyse_line(file_path, node->d_name, &new_list.student_info[i]);
					}
					else if (strcmp(argv[1], "-checktitle") == 0)
					{
						read_check(file_path, node->d_name, &new_list.student_info[i]);
					}
					else
					{
						printf("功能参数错误\n");
						return 0;
					}
				}

			}

			closedir(dir);
#endif 

			printf("\n");
		}
	}

	fclose(infile);
	return 0;
}

//该函数检查用户在命令行参数中提供的文件名后缀是否符合要求
int check_file_extension(char *filename)
{
	int match = 0;
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
int check_class(char *class_0, char *class_1, char *class_2)
{
	int match = 0;

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
void check_first_line(char(*first_line_info)[20], char(*to_be_check)[20], struct Student *student)
{
	/********检查是否成功读取到首行信息  以及信息项是否缺失或多余********/
	if (strcmp(first_line_info[0], "//") == 0)
	{
		//在第一段字符串为//的情况下，只可能有四段字符串
		if (first_line_info[4][0] != 0)
		{
			student->info_num_check = -1;
		}
		else if (first_line_info[3][0] == 0)
		{
			student->info_num_check = 0;
		}
		else
		{
			student->info_num_check = 1;
			strcpy(to_be_check[0], first_line_info[1]);
			strcpy(to_be_check[1], first_line_info[2]);
			strcpy(to_be_check[2], first_line_info[3]);
		}
	}
	else if (strncmp(first_line_info[0], "//", 2) == 0)
	{
		if (first_line_info[3][0] != 0)
		{
			student->info_num_check = -1;
		}
		else if (first_line_info[2][0] == 0)
		{
			student->info_num_check = 0;
		}
		else
		{
			student->info_num_check = 1;
			strcpy(to_be_check[0], first_line_info[0] + 2);
			strcpy(to_be_check[1], first_line_info[1]);
			strcpy(to_be_check[2], first_line_info[2]);
		}
	}
	else if (strcmp(first_line_info[0], "/*") == 0)
	{
		int end_exist = 0;
		int end_pos;
		for (end_pos = 0; end_pos < 6; end_pos++)
		{
			if (annotation_end(first_line_info[end_pos]) == 1)
			{
				end_exist = 1;
				if (end_pos < 4) student->info_num_check = 0;
				else if (end_pos>4) student->info_num_check = -1;
				else student->info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[1]);
				strcpy(to_be_check[1], first_line_info[2]);
				strcpy(to_be_check[2], first_line_info[3]);

				break;
			}

			else if (annotation_end(first_line_info[end_pos]) == -1)
			{
				end_exist = 1;
				if (end_pos < 3) student->info_num_check = 0;
				else if (end_pos>3) student->info_num_check = -1;
				else student->info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[1]);
				strcpy(to_be_check[1], first_line_info[2]);
				strcpy(to_be_check[2], first_line_info[3]);
				to_be_check[2][strlen(first_line_info[3]) - 2] = '\0';

				break;
			}
		}
		if (!end_exist) student->line_read_success = 0;
	}
	else if (strncmp(first_line_info[0], "/*", 2) == 0)
	{
		int end_exist = 0;
		int end_pos;
		for (end_pos = 0; end_pos < 6; end_pos++)
		{
			if (annotation_end(first_line_info[end_pos]) == 1)
			{
				end_exist = 1;
				if (end_pos < 3) student->info_num_check = 0;
				else if (end_pos>3) student->info_num_check = -1;
				else student->info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[0] + 2);
				strcpy(to_be_check[1], first_line_info[1]);
				strcpy(to_be_check[2], first_line_info[2]);
				break;
			}

			else if (annotation_end(first_line_info[end_pos]) == -1)
			{
				end_exist = 1;
				if (end_pos < 2) student->info_num_check = 0;
				else if (end_pos>2) student->info_num_check = -1;
				else student->info_num_check = 1;

				strcpy(to_be_check[0], first_line_info[0] + 2);
				strcpy(to_be_check[1], first_line_info[1]);
				strcpy(to_be_check[2], first_line_info[2]);
				to_be_check[2][strlen(first_line_info[2]) - 2] = '\0';
				break;
			}
		}

		if (!end_exist) student->line_read_success = 0;
	}
	else student->line_read_success = 0;
}

/********检查首行信息是否匹配********/
void check_info_match(char(*to_be_check)[20], struct Student *student)
{
	int j;

	if (student->line_read_success)
	{
		/********检查首行信息是否匹配********/
		if (student->info_num_check == 1)
		{
			//检查学号
			for (j = 0; j < 3; j++)
			{
				if (strcmp(student->no, to_be_check[j]) == 0)
				{
					student->no_check = 1;
					break;
				}
			}

			//检查姓名
			for (j = 0; j < 3; j++)
			{
				if (strcmp(student->name, to_be_check[j]) == 0)
				{
					student->name_check = 1;
					break;
				}
			}

			for (j = 0; j < 3; j++)
			{
				if (check_class(to_be_check[j], student->class_1, student->class_2))
				{
					student->class_check = 1;
					break;
				}
			}
		}
	}
}

/********根据判定打印检查结果********/
void print_result(struct Student *student, char *filename)
{
	printf("%s ", student->no);
	printf("%s ", student->name);
	printf("%s:", filename);

	if (!student->hand_in)
	{
		printf("未提交\n");
		return;
	}
	if (!student->line_read_success)
	{
		printf("未取到首行信息\n");
		return;
	}
	else if (student->info_num_check == 0)
	{
		printf("首行信息不全\n");
		return;
	}
	else if (student->info_num_check == -1)
	{
		printf("首行信息过多\n");
		return;
	}

	if (!student->no_check)
	{
		printf("学号不匹配 ");
		student->pass = 0;
	}

	if (!student->name_check)
	{
		printf("姓名不匹配 ");
		student->pass = 0;
	}

	if (!student->class_check)
	{
		printf("班级不匹配 ");
		student->pass = 0;
	}

	if (student->pass)
	{
		printf("通过");
	}
	printf("\n");
}

//学生个体作业检查情况的初始化
void student_stat_init(struct Student *student)
{
	student->hand_in = 0;
	student->no_check = 0;
	student->name_check = 0;
	student->class_check = 0;
	student->info_num_check = 0; //1表示信息完整，0表示信息不全，-1表示信息过多
	student->line_read_success = 1; //是否取到首行信息
	student->pass = 1;
}

//读取作业文件和检查的主体部分
void read_check(char *file_path, char *filename, struct Student *student)
{
	char to_be_check[3][20];
	FILE *check_file;

	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		//文件打不开，则判定名单中该学生未交作业
		student->hand_in = 0;
	}
	else
	{
		//判定作业已提交
		student->hand_in = 1;

		//临时字符串数组存储所读的首行信息
		char first_line_info[6][20] = { 0 };

		//将文件首行内容读取至字符串流
		char first_line[100];
		fscanf(check_file, "%s", first_line);
		fgets(first_line + strlen(first_line), 100, check_file);

		//将字符串流中的信息输入到first_line_info字符串数组
		sscanf(first_line, "%s%s%s%s%s%s",
			first_line_info[0], first_line_info[1],
			first_line_info[2], first_line_info[3],
			first_line_info[4], first_line_info[5]);

		check_first_line(first_line_info, to_be_check, student);

		check_info_match(to_be_check, student);

		fclose(check_file);
	}

	print_result(student, filename);

}

//统计文件中的总行数
void count_line(char *file_path, char *filename, Student *student)
{
	int linecount = 0;
	char ch;

	FILE *check_file;
	check_file = fopen(file_path, "r");

	if (check_file==NULL)
	{
		//文件打不开，则判定名单中该学生未交作业
		student->hand_in = 0;
	}
	else
	{
		//判定作业已提交
		student->hand_in = 1;

		//每一个回车算作一行的话，那我就统计文本中\n的数量不就好了
		while (!feof(check_file))
		{
			ch = fgetc(check_file);
			if (ch == '\n')
				linecount++;
		}

		student->linecount = linecount;
	}

	//打印检查结果
	printf("%s-%s : %s : ", student->no, student->name, filename);

	if (student->hand_in)
	{
		printf("共%d行", student->linecount);
	}
	else
	{
		printf("%s-%s : %s : ", student->no, student->name, filename);
		printf("未提交\n");
	}

	//关闭文件
	fclose(check_file);
}

//源代码文件各项内容行数的分析
void analyse_line(char *file_path, char *filename, Student *student)
{
	meaningful_line(file_path, filename, student);
	annotation_line(file_path, filename, student);
	with_annotation_line(file_path, filename, student);
	valid_char_num(file_path, filename, student);
	valid_anno_char(file_path, filename, student);

	if (student->hand_in)
	{
		printf("%s-%s : %s : ", student->no, student->name, filename);
		printf("有效行-%d ", student->meaningful_line);
		printf("纯注释行-%d ", student->annotation_line);
		printf("注释行-%d ", student->with_annotation_line);
		printf("有效字符-%d ", student->valid_char_num);
		printf("注释字符-%d ", student->valid_anno_char);
		printf("比例-%0.2lf", ((double)(student->valid_anno_char) / (double)(student->valid_char_num)) * 100);
		printf("%%\n");
	}
	else
	{
		printf("%s-%s : %s : ", student->no, student->name, filename);
        printf("未提交\n");
	}
}

//统计有内容的总行数
void meaningful_line(char  *file_path, char *filename, Student *student)
{
	int meaningful_line = 0;

	FILE *check_file;
	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		student->hand_in = 0;
	}
	else
	{
		student->hand_in = 1;

		char line[MAX_LINE_CHAR_NUM] = { 0 };
		while (fgets(line,MAX_LINE_CHAR_NUM,check_file))
		{
			int meaningful = 0;

			for (int i = 0; i < strlen(line); i++)
			{
				if (meaningful_char(line[i]))
				{
					meaningful = 1;
					break;
				}
			}

			if (meaningful)
				meaningful_line++;
		}

		student->meaningful_line = meaningful_line;
	}

	fclose(check_file);
}

//判断某个字符是否为有意义字符（非空格/TAB/回车/换行）
int meaningful_char(char ch)
{
	if (ch == 0x20)
		return 0;
	else if (ch == 0x0a)
		return 0;
	else if (ch == 0x09)
		return 0;
	else if (ch == 0x0d)
		return 0;
	else if (ch == 0)
		return 0;
	else return 1;
}

//统计纯注释语句的行数
void annotation_line(char *file_path, char *filename, Student *student)
{
	int annotation_line = 0;

	FILE *check_file;

	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		student->hand_in = 0;
	}
	else
	{
		student->hand_in = 1;

		char line[MAX_LINE_CHAR_NUM] = { 0 };
		while (fgets(line, MAX_LINE_CHAR_NUM, check_file))
		{
			//若“//”出现在字符串头部则该行为纯注释
			if (find_annotation(line, "//") == HEAD)
			{
				annotation_line++;
			}
			//若“/*”在头部，“*/”在尾部则该行为纯注释
			else if (find_annotation(line, "/*") == HEAD && find_annotation(line, "*/") == END)
			{
				annotation_line++;
			}
			//仅存在“*/”在尾部的也说明该行为纯注释
			else if (find_annotation(line, "/*") == FAIL && find_annotation(line, "*/") == END)
			{
				annotation_line++;
			}
		}

		student->annotation_line = annotation_line;
	}

	fclose(check_file);
}

//去除字符串头部和尾部的空格
char *alltrim(char *buf)
{
	char *p;
	/*去除尾部空格*/
	p = &buf[strlen(buf) - 1];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p--;
	}
	*(p + 1) = 0;

	/*去除头部空格*/
	p = &buf[0];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p++;
	}
	/*p移动到buf，含尾零*/
	if (p != buf)
	{
		memmove(buf, p, strlen(p) + 1);
	}

	return buf;
}

//在字符串中寻找注释的标记
int find_annotation(char *source, const char *target)
{
	//先把字符串的头尾非有效字符去掉
	strcpy(source, alltrim(source));

	for (int i = 0; i < (int)(strlen(source)) - 1; i++)
	{
		if (source[i] == target[0] && source[i + 1] == target[1])
		{
			//注释标记在头部
			if (i == 0)
			{
				return HEAD;
			}
			//注释标记在尾部
			else if (i == strlen(source) - 2)
			{
				return END;
			}
			else return BETWEEN;
		}
	}

	return FAIL;
}

//统计含注释语句的行数
void with_annotation_line(char *file_path, char *filename, Student *student)
{
	int with_annotation_line = 0;
	FILE *check_file;

	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		student->hand_in = 0;
	}
	else
	{
		student->hand_in = 1;
		char line[MAX_LINE_CHAR_NUM] = { 0 };

		while (fgets(line, MAX_LINE_CHAR_NUM, check_file))
		{
			if (find_annotation(line, "//") == BETWEEN)
			{
				with_annotation_line++;
			}
			else if (find_annotation(line, "/*") != HEAD && find_annotation(line, "/*"))
			{
				with_annotation_line++;
			}
			else if (find_annotation(line, "*/") != END && find_annotation(line, "*/"))
			{
				with_annotation_line++;
			}
		}

		student->with_annotation_line = with_annotation_line;
	}
#if 0
	//打印检查结果
	cout << student.no << "-" << student.name << " : " << filename << " : ";

	if (student.hand_in)
	{
		cout << "共" << student.with_annotation_line << "行" << endl;
	}
	else cout << "未提交" << endl;
#endif 
	fclose(check_file);
}

//统计源文件中有效字符数
void valid_char_num(char *file_path, char *filename, Student *student)
{
	int valid_char_num = 0;
	char ch;
	FILE *check_file;

	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		student->hand_in = 0;
	}
	else
	{
		student->hand_in = 1;

		while (!feof(check_file))
		{
			ch = fgetc(check_file);

			if (meaningful_char(ch))
			{
				valid_char_num++;
			}
		}

		student->valid_char_num = valid_char_num;
	}

#if 0
	//打印检查结果
	cout << student.no << "-" << student.name << " : " << filename << " : ";

	if (student.hand_in)
	{
		cout << "共" << student.valid_char_num << "行" << endl;
	}
	else cout << "未提交" << endl;
#endif

	fclose(check_file);
}

//统计注释语句的有效字符数
void valid_anno_char(char *file_path, char *filename, Student *student)
{
	int valid_anno_char = 0;
	char *ptr;
	FILE *check_file;

	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		student->hand_in = 0;
	}
	else
	{
		student->hand_in = 1;

		char line[MAX_LINE_CHAR_NUM] = { 0 };
		while (fgets(line, MAX_LINE_CHAR_NUM, check_file))
		{
			//该行存在“//”注释
			if (find_annotation(line, "//") != FAIL)
			{
				//将指针指向第一个"/"
				ptr = line;
				for (int i = 0; i < strlen(line); i++)
				{
					if (*ptr == '/')
						break;

				}

				//从“/”开始到本行结束统计有效字符
				for (; *ptr != '\0'; ptr++)
				{
					if (meaningful_char(*ptr))
						valid_anno_char++;
				}
			}

			//该行存在“/*”注释
			else if (find_annotation(line, "/*") != FAIL)
			{
				//将指针指向第一个"/"
				ptr = line;
				for (int i = 0; i < strlen(line); i++)
				{
					if (*ptr == '/')
						break;
				}
				valid_anno_char++;

				//从“/”开始到本行结束统计有效字符
				for (ptr = ptr + 1; *ptr != '\0' && *ptr != '/'; ptr++)
				{
					if (meaningful_char(*ptr))
						valid_anno_char++;
				}

				//如果是以“/”结尾的话还要再添一个
				if (*ptr == '/') valid_anno_char++;
			}

			//该行存在“*/”注释
			else if (find_annotation(line, "*/") != FAIL)
			{
				ptr = line;

				//从字符串开头到“/”统计有效字符
				for (; *ptr != '/'; ptr++)
				{
					if (meaningful_char(*ptr))
						valid_anno_char++;
				}

				valid_anno_char++;
			}

		}

		student->valid_anno_char = valid_anno_char;
	}

#if 0
	//打印检查结果
	cout << student.no << "-" << student.name << " : " << filename << " : ";

	if (student.hand_in)
	{
		cout << "共" << student.valid_anno_char << "行" << endl;
	}
	else cout << "未提交" << endl;
#endif

	fclose(check_file);
}