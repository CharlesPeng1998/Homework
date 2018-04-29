/*1751367 ��2 ����*/
/*1750455 ��껶� 1751737 ������ 1750034 ��һ٫ 1752071 ��ƽ�� 1751456 ʯ��� 1751988 ���ź�*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	char *filename = (char *)malloc(50);
	char ch;

	//����Ƿ���������в���
	if (argc > 1)
		filename = argv[1];
	else
	{
		char input_filename[50];//�����û�������ļ���
		fprintf(stdout, "�ļ���������ʽ�����ԣ�\n");
		fprintf(stdout, "    a.txt������·����ʽ\n");
		fprintf(stdout, "    ..\\data\\b.dat�����·����ʽ\n");
		fprintf(stdout, "    C:\\Windows\\System32\\c.dat���������·����ʽ\n");
		fprintf(stdout, "�������ļ�����");
		scanf("%s", input_filename);

		strcpy(filename, input_filename);
	}

	FILE *infile;
	infile = fopen(filename, "rb");
	//������
	if (infile == NULL)
	{
		fprintf(stderr, "�ļ���ʧ��\n");
		return -1;
	}

	int curr_pos = 0;//��¼�������ַ���λ��

	while (!feof(infile))
	{
		char curr_line[17];//��¼���е��ַ�
		int curr_line_ascii[16] = { 0 };//��¼����ÿ���ַ���ASCIIֵ

		int count;
		for (count = 0; count < 16; count++)
		{
			if (!feof(infile))
			{
				ch = fgetc(infile);

				if (ch >= 33 && ch <= 126)
					curr_line[count] = ch;
				else curr_line[count] = '.';

				curr_line_ascii[count] = (int)(unsigned char)(ch);
			}
			else //�ļ�����ʱ����һ���������һ
			{
				count--;
				break;
			}
		}

		curr_line[count] = '\0'; //�����ַ������β0

		//��ӡÿ��
		fprintf(stdout, "%08x  ", curr_pos);

		if (count > 8)
		{
			int i;
			for (i = 0; i < 8; i++)
			{
				fprintf(stdout, "%02x ", curr_line_ascii[i]);
			}

			fprintf(stdout, "- ");

			for (i = 8; i < count; i++)
			{
				fprintf(stdout, "%02x ", curr_line_ascii[i]);
			}

			for (i = count; i < 16; i++)
			{
				fprintf(stdout, "   ");
			}
		}

		else
		{
			int i;
			for (i = 0; i < count; i++)
			{
				fprintf(stdout, "%02x ", curr_line_ascii[i]);
			}

			for (i = count; i < 8; i++)
			{
				fprintf(stdout, "   ");
			}

			fprintf(stdout, "  ");

			for (i = 8; i < 16; i++)
			{
				fprintf(stdout, "   ");
			}
		}

		fprintf(stdout, "    %s\n", curr_line);
		curr_pos += 16;
	}

	fclose(infile);
	return 0;
}