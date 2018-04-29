/*1751367 ��2 ����*/
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

//���������ѧ������
#define MAX_STUDENT_NUM 12
#define MAX_LINE_CHAR_NUM 256 //һ���������ַ�����

//Ѱ��ע��ͷβ�����ķ���ֵ���
#define HEAD 1 //���ַ���ͷ��
#define END 2 //���ַ���β��
#define BETWEEN 3 //���ַ����м䲿��
#define FAIL 0 //���������ַ�����

//ѧ����Ϣ�ṹ��
typedef struct Student
{
	char no[10];
	char name[10];

	//�γ������а༶��������ʽ: һ��/1��
	char class_1[10];
	char class_2[10];

	//���Ľ��
	int hand_in;
	int no_check;
	int name_check;
	int class_check;
	int info_num_check; //1��ʾ��Ϣ������0��ʾ��Ϣ��ȫ��-1��ʾ��Ϣ����
	int line_read_success; //�Ƿ�ȡ��������Ϣ
	int pass;

	int linecount; //��ҵ�ļ�������
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

/***************************����ԭ��********************************/
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
		printf("������������\n");
		return -1;
	}

	/********���ȴ�dat�ļ��ж�ȡָ���γ̵�����ѧ����Ϣ********/

	//��ȡ��Ϣ���ļ�
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
		printf("δ�ܶ�ȡ��ѧ����������ȷ��source�ļ��е�·���Ƿ���ȷ\n");
		return -1;
	}

	//���ļ������ж�ȡѧ��������Ϣ
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
	/****************����ѧ����Ϣ��ȡ���****************/

	if (strcmp(argv[3], "all"))
	{
		//����û��ṩ���ļ�����׺�Ƿ����Ҫ��
		if (!check_file_extension(argv[3]))
		{
			printf("����Դ�����ļ�\n");
			return 0;
		}

		//�����ѧ�������ж�Ӧ��ѧ���ļ��в����
		for (i = 0; i < new_list.student_num; i++)
		{
			student_stat_init(&new_list.student_info[i]);

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
				printf("���ܲ�������\n");
				return 0;
			}
		}
	}
	else
	{
		//�����в����ṩ"all"������Ҫ��������ļ�
		//����ʲô�ļ��ͼ��ʲô�ļ���δ�ύ�ľͲ�����

#if defined(_MSC_VER)		
		struct _finddata_t file;
		intptr_t k;
		intptr_t HANDLE; //��¼��һ�δ򿪵��ļ�������ر�ʱ���ô�ֵ
#elif defined(__linux) || defined(__linux__)
		DIR            *dir;
		struct dirent  *node;
#endif 

		for (i = 0; i < new_list.student_num; i++)
		{
#if defined(_MSC_VER)
			//�ļ�·������ʼΪsource��
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
						printf("���ܲ�������\n");
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
				//�������δ�ύ��Ҫ������
				continue;
			}

			/* ѭ��ɨ���Ŀ¼�µ������ļ� */
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
						printf("���ܲ�������\n");
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

//�ú�������û��������в������ṩ���ļ�����׺�Ƿ����Ҫ��
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
int check_class(char *class_0, char *class_1, char *class_2)
{
	int match = 0;

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
void check_first_line(char(*first_line_info)[20], char(*to_be_check)[20], struct Student *student)
{
	/********����Ƿ�ɹ���ȡ��������Ϣ  �Լ���Ϣ���Ƿ�ȱʧ�����********/
	if (strcmp(first_line_info[0], "//") == 0)
	{
		//�ڵ�һ���ַ���Ϊ//������£�ֻ�������Ķ��ַ���
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

/********���������Ϣ�Ƿ�ƥ��********/
void check_info_match(char(*to_be_check)[20], struct Student *student)
{
	int j;

	if (student->line_read_success)
	{
		/********���������Ϣ�Ƿ�ƥ��********/
		if (student->info_num_check == 1)
		{
			//���ѧ��
			for (j = 0; j < 3; j++)
			{
				if (strcmp(student->no, to_be_check[j]) == 0)
				{
					student->no_check = 1;
					break;
				}
			}

			//�������
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

/********�����ж���ӡ�����********/
void print_result(struct Student *student, char *filename)
{
	printf("%s ", student->no);
	printf("%s ", student->name);
	printf("%s:", filename);

	if (!student->hand_in)
	{
		printf("δ�ύ\n");
		return;
	}
	if (!student->line_read_success)
	{
		printf("δȡ��������Ϣ\n");
		return;
	}
	else if (student->info_num_check == 0)
	{
		printf("������Ϣ��ȫ\n");
		return;
	}
	else if (student->info_num_check == -1)
	{
		printf("������Ϣ����\n");
		return;
	}

	if (!student->no_check)
	{
		printf("ѧ�Ų�ƥ�� ");
		student->pass = 0;
	}

	if (!student->name_check)
	{
		printf("������ƥ�� ");
		student->pass = 0;
	}

	if (!student->class_check)
	{
		printf("�༶��ƥ�� ");
		student->pass = 0;
	}

	if (student->pass)
	{
		printf("ͨ��");
	}
	printf("\n");
}

//ѧ��������ҵ�������ĳ�ʼ��
void student_stat_init(struct Student *student)
{
	student->hand_in = 0;
	student->no_check = 0;
	student->name_check = 0;
	student->class_check = 0;
	student->info_num_check = 0; //1��ʾ��Ϣ������0��ʾ��Ϣ��ȫ��-1��ʾ��Ϣ����
	student->line_read_success = 1; //�Ƿ�ȡ��������Ϣ
	student->pass = 1;
}

//��ȡ��ҵ�ļ��ͼ������岿��
void read_check(char *file_path, char *filename, struct Student *student)
{
	char to_be_check[3][20];
	FILE *check_file;

	check_file = fopen(file_path, "r");

	if (check_file == NULL)
	{
		//�ļ��򲻿������ж������и�ѧ��δ����ҵ
		student->hand_in = 0;
	}
	else
	{
		//�ж���ҵ���ύ
		student->hand_in = 1;

		//��ʱ�ַ�������洢������������Ϣ
		char first_line_info[6][20] = { 0 };

		//���ļ��������ݶ�ȡ���ַ�����
		char first_line[100];
		fscanf(check_file, "%s", first_line);
		fgets(first_line + strlen(first_line), 100, check_file);

		//���ַ������е���Ϣ���뵽first_line_info�ַ�������
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

//ͳ���ļ��е�������
void count_line(char *file_path, char *filename, Student *student)
{
	int linecount = 0;
	char ch;

	FILE *check_file;
	check_file = fopen(file_path, "r");

	if (check_file==NULL)
	{
		//�ļ��򲻿������ж������и�ѧ��δ����ҵ
		student->hand_in = 0;
	}
	else
	{
		//�ж���ҵ���ύ
		student->hand_in = 1;

		//ÿһ���س�����һ�еĻ������Ҿ�ͳ���ı���\n���������ͺ���
		while (!feof(check_file))
		{
			ch = fgetc(check_file);
			if (ch == '\n')
				linecount++;
		}

		student->linecount = linecount;
	}

	//��ӡ�����
	printf("%s-%s : %s : ", student->no, student->name, filename);

	if (student->hand_in)
	{
		printf("��%d��", student->linecount);
	}
	else
	{
		printf("%s-%s : %s : ", student->no, student->name, filename);
		printf("δ�ύ\n");
	}

	//�ر��ļ�
	fclose(check_file);
}

//Դ�����ļ��������������ķ���
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
		printf("��Ч��-%d ", student->meaningful_line);
		printf("��ע����-%d ", student->annotation_line);
		printf("ע����-%d ", student->with_annotation_line);
		printf("��Ч�ַ�-%d ", student->valid_char_num);
		printf("ע���ַ�-%d ", student->valid_anno_char);
		printf("����-%0.2lf", ((double)(student->valid_anno_char) / (double)(student->valid_char_num)) * 100);
		printf("%%\n");
	}
	else
	{
		printf("%s-%s : %s : ", student->no, student->name, filename);
        printf("δ�ύ\n");
	}
}

//ͳ�������ݵ�������
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

//�ж�ĳ���ַ��Ƿ�Ϊ�������ַ����ǿո�/TAB/�س�/���У�
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

//ͳ�ƴ�ע����������
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
			//����//���������ַ���ͷ�������Ϊ��ע��
			if (find_annotation(line, "//") == HEAD)
			{
				annotation_line++;
			}
			//����/*����ͷ������*/����β�������Ϊ��ע��
			else if (find_annotation(line, "/*") == HEAD && find_annotation(line, "*/") == END)
			{
				annotation_line++;
			}
			//�����ڡ�*/����β����Ҳ˵������Ϊ��ע��
			else if (find_annotation(line, "/*") == FAIL && find_annotation(line, "*/") == END)
			{
				annotation_line++;
			}
		}

		student->annotation_line = annotation_line;
	}

	fclose(check_file);
}

//ȥ���ַ���ͷ����β���Ŀո�
char *alltrim(char *buf)
{
	char *p;
	/*ȥ��β���ո�*/
	p = &buf[strlen(buf) - 1];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p--;
	}
	*(p + 1) = 0;

	/*ȥ��ͷ���ո�*/
	p = &buf[0];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p++;
	}
	/*p�ƶ���buf����β��*/
	if (p != buf)
	{
		memmove(buf, p, strlen(p) + 1);
	}

	return buf;
}

//���ַ�����Ѱ��ע�͵ı��
int find_annotation(char *source, const char *target)
{
	//�Ȱ��ַ�����ͷβ����Ч�ַ�ȥ��
	strcpy(source, alltrim(source));

	for (int i = 0; i < (int)(strlen(source)) - 1; i++)
	{
		if (source[i] == target[0] && source[i + 1] == target[1])
		{
			//ע�ͱ����ͷ��
			if (i == 0)
			{
				return HEAD;
			}
			//ע�ͱ����β��
			else if (i == strlen(source) - 2)
			{
				return END;
			}
			else return BETWEEN;
		}
	}

	return FAIL;
}

//ͳ�ƺ�ע����������
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
	//��ӡ�����
	cout << student.no << "-" << student.name << " : " << filename << " : ";

	if (student.hand_in)
	{
		cout << "��" << student.with_annotation_line << "��" << endl;
	}
	else cout << "δ�ύ" << endl;
#endif 
	fclose(check_file);
}

//ͳ��Դ�ļ�����Ч�ַ���
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
	//��ӡ�����
	cout << student.no << "-" << student.name << " : " << filename << " : ";

	if (student.hand_in)
	{
		cout << "��" << student.valid_char_num << "��" << endl;
	}
	else cout << "δ�ύ" << endl;
#endif

	fclose(check_file);
}

//ͳ��ע��������Ч�ַ���
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
			//���д��ڡ�//��ע��
			if (find_annotation(line, "//") != FAIL)
			{
				//��ָ��ָ���һ��"/"
				ptr = line;
				for (int i = 0; i < strlen(line); i++)
				{
					if (*ptr == '/')
						break;

				}

				//�ӡ�/����ʼ�����н���ͳ����Ч�ַ�
				for (; *ptr != '\0'; ptr++)
				{
					if (meaningful_char(*ptr))
						valid_anno_char++;
				}
			}

			//���д��ڡ�/*��ע��
			else if (find_annotation(line, "/*") != FAIL)
			{
				//��ָ��ָ���һ��"/"
				ptr = line;
				for (int i = 0; i < strlen(line); i++)
				{
					if (*ptr == '/')
						break;
				}
				valid_anno_char++;

				//�ӡ�/����ʼ�����н���ͳ����Ч�ַ�
				for (ptr = ptr + 1; *ptr != '\0' && *ptr != '/'; ptr++)
				{
					if (meaningful_char(*ptr))
						valid_anno_char++;
				}

				//������ԡ�/����β�Ļ���Ҫ����һ��
				if (*ptr == '/') valid_anno_char++;
			}

			//���д��ڡ�*/��ע��
			else if (find_annotation(line, "*/") != FAIL)
			{
				ptr = line;

				//���ַ�����ͷ����/��ͳ����Ч�ַ�
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
	//��ӡ�����
	cout << student.no << "-" << student.name << " : " << filename << " : ";

	if (student.hand_in)
	{
		cout << "��" << student.valid_anno_char << "��" << endl;
	}
	else cout << "δ�ύ" << endl;
#endif

	fclose(check_file);
}