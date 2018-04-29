/*1751367 ��2 ����*/
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

//���������ѧ������
#define MAX_STUDENT_NUM 12

using namespace std;

//ѧ����Ϣ�ṹ��
struct Student
{
	char no[10];
	char name[10];

	//�γ������а༶��������ʽ: һ��/1��
	char class_1[10];
	char class_2[10];

	//���Ľ��
	bool hand_in;
	bool no_check;
	bool name_check;
	bool class_check;
	int info_num_check; //1��ʾ��Ϣ������0��ʾ��Ϣ��ȫ��-1��ʾ��Ϣ����
	bool line_read_success; //�Ƿ�ȡ��������Ϣ
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
		cout << "������������" << endl;
		return -1;
	}

	if (strcmp(argv[1], "-checktitle"))
	{
		cout << "���ܲ�������" << endl;
		return -1;
	}

	/********���ȴ�dat�ļ��ж�ȡָ���γ̵�����ѧ����Ϣ********/

	//��ȡ��Ϣ���ļ�
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
		cout << "�޷��򿪿γ���������ȷ��source�ļ���·���Ƿ���ȷ" << endl;
		return -1;
	}

	//���ļ������ж�ȡѧ��������Ϣ
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

	//�����в������ṩָ���ļ����ļ��
	if (strcmp(argv[3], "all"))
	{
		//����û��ṩ���ļ�����׺�Ƿ����Ҫ��
		if (!check_file_extension(argv[3]))
		{
			cout << "����Դ�����ļ�" << endl;
			return 0;
		}

		//�����ѧ�������ж�Ӧ��ѧ���ļ��в����
		for (int i = 0; i < new_list.student_num; i++)
		{
			student_stat_init(new_list.student_info[i]);

			char to_be_check[3][20];
			//�ļ�·������ʼΪsource��
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
		//�����в����ṩ"all"������Ҫ��������ļ�
		//����ʲô�ļ��ͼ��ʲô�ļ���δ�ύ�ľͲ�����

#if defined(_MSC_VER)		
		_finddata_t file;
		intptr_t k;
		intptr_t HANDLE; //��¼��һ�δ򿪵��ļ�������ر�ʱ���ô�ֵ
#elif defined(__linux) || defined(__linux__)
		DIR            *dir;
		struct dirent  *node;
#endif 

		for (int i = 0; i < new_list.student_num; i++)
		{
#if defined(_MSC_VER)
			//�ļ�·������ʼΪsource��
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
				//�������δ�ύ��Ҫ������
				continue;
			}

			/* ѭ��ɨ���Ŀ¼�µ������ļ� */
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

//�ú�������û��������в������ṩ���ļ�����׺�Ƿ����Ҫ��
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

//�ú��������ж�һ���ַ������Ƿ���"*/"
int annotation_end(char *str)
{
	//��ʵ���ǿ�һ���ַ����Ƿ���*/�����ҿ�*/����Ϊ�����ַ������ڻ��ǽ�����ַ���β��
	if (strcmp(str, "*/") == 0)
		return 1;
	else if (str[strlen(str) - 1] == '/' && str[strlen(str) - 2] == '*')
		return -1;
	else return 0;
}

//�ú������ڼ��ĳ���ַ����Ƿ���༶ƥ��
bool check_class(char *class_0, char *class_1, char *class_2)
{
	bool match = 0;

	//������ȡ������ַ���������ĸ��ֽ�,������������
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

	//����ȡ��������ֽڣ���������2��
	strcpy(to_be_check, class_0 + strlen(class_0) - 3);

	if (strcmp(to_be_check, class_1) == 0)
	{
		match = 1;
	}
	else if (strcmp(to_be_check, class_2) == 0)
	{
		match = 1;
	}

	//Ȼ��Ҫ������ǿ������ǿ����������������
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

/********����Ƿ�ɹ���ȡ��������Ϣ  �Լ���Ϣ���Ƿ�ȱʧ�����********/
void check_first_line(char(*first_line_info)[20], char(*to_be_check)[20], Student &student)
{
	/********����Ƿ�ɹ���ȡ��������Ϣ  �Լ���Ϣ���Ƿ�ȱʧ�����********/
	if (strcmp(first_line_info[0], "//") == 0)
	{
		//�ڵ�һ���ַ���Ϊ//������£�ֻ�������Ķ��ַ���
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

/********���������Ϣ�Ƿ�ƥ��********/
void check_info_match(char(*to_be_check)[20], Student &student)
{
	if (student.line_read_success)
	{
		/********���������Ϣ�Ƿ�ƥ��********/
		if (student.info_num_check == 1)
		{
			//���ѧ��
			for (int j = 0; j < 3; j++)
			{
				if (strcmp(student.no, to_be_check[j]) == 0)
				{
					student.no_check = 1;
					break;
				}
			}

			//�������
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

/********�����ж���ӡ�����********/
void print_result(Student &student, char *filename)
{
	cout << student.no << ' ';
	cout << student.name << ' ';
	cout << filename << ':';

	if (!student.hand_in)
	{
		cout << "δ�ύ" << endl;
		return;
	}
	if (!student.line_read_success)
	{
		cout << "δȡ��������Ϣ" << endl;
		return;
	}
	else if (student.info_num_check == 0)
	{
		cout << "������Ϣ��ȫ" << endl;
		return;
	}
	else if (student.info_num_check == -1)
	{
		cout << "������Ϣ����" << endl;
		return;
	}

	if (!student.no_check)
	{
		cout << "ѧ�Ų�ƥ�� ";
		student.pass = 0;
	}

	if (!student.name_check)
	{
		cout << "������ƥ�� ";
		student.pass = 0;
	}

	if (!student.class_check)
	{
		cout << "�༶��ƥ�� ";
		student.pass = 0;
	}

	if (student.pass)
	{
		cout << "ͨ��";
	}
	cout << endl;
}

//ѧ��������ҵ�������ĳ�ʼ��
void student_stat_init(Student &student)
{
	student.hand_in = 0;
	student.no_check = 0;
	student.name_check = 0;
	student.class_check = 0;
	student.info_num_check = 0; //1��ʾ��Ϣ������0��ʾ��Ϣ��ȫ��-1��ʾ��Ϣ����
	student.line_read_success = 1; //�Ƿ�ȡ��������Ϣ
	student.pass = 1;
}

//��ȡ��ҵ�ļ��ͼ������岿��
void read_check(char *file_path, char *filename, Student &student)
{
	char to_be_check[3][20];
	ifstream check_file(file_path, ios::in);

	if (!check_file.is_open())
	{
		//�ļ��򲻿������ж������и�ѧ��δ����ҵ
		student.hand_in = 0;
	}
	else
	{
		//�ж���ҵ���ύ
		student.hand_in = 1;

		//��ʱ�ַ�������洢������������Ϣ
		char first_line_info[6][20] = { 0 };

		//���ļ��������ݶ�ȡ���ַ�����
		istringstream istr;
		char first_line[100];
		check_file >> first_line;
		check_file.getline((first_line + strlen(first_line)), 100, '\n');

		istr.str(first_line);

		//���ַ������е���Ϣ���뵽first_line_info�ַ�������
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