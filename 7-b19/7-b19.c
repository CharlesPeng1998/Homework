/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int is_Windows(char *filename);

int main(int argc,char *argv[])
{
	char ch;

	if (argc < 3)
	{
		fprintf(stdout, "������������\n");
		return -1;
	}

	//��������в���
	else if (strcmp(argv[1], "-check") == 0)
	{
		int is_windows = is_Windows(argv[2]);
		switch (is_windows)
		{
			case 1:fprintf(stdout, "Windows��ʽ\n"); break;
			case 0:fprintf(stdout, "Linux��ʽ\n"); break;
			case -1:break;
		}
	}

	else if (strcmp(argv[1], "-convert") == 0)
	{
		if (strcmp(argv[2], "wtol") == 0)
		{
			//�����Ҫת�����ļ��Ƿ�Ϊwindows�ı��ļ�
			if (is_Windows(argv[3]) == 0)
			{
				fprintf(stdout, "�ļ���ʽ����\n");
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//�򿪴�ת�����ļ�
			FILE *infile;
			infile = fopen(argv[3], "rb");

			//�򿪽���ת�����ı����ļ�
			FILE *outfile;
			outfile = fopen(argv[4], "wb");
			//�ļ���ȡ������
			if (outfile == NULL)
			{
				fprintf(stderr, "�޷����ļ�\n");
				fclose(infile);
				return -1;
			}

			while (!feof(infile))
			{
				ch = fgetc(infile);
				if (ch != '\r')
					fputc(ch, outfile);
			}

			fclose(infile);
			fclose(outfile);
		}

		else if (strcmp(argv[2], "ltow") == 0)
		{
			//�����Ҫת�����ļ��Ƿ�Ϊlinux�ı��ļ�
			if (is_Windows(argv[3]) == 1)
			{
				fprintf(stdout, "�ļ���ʽ����\n");
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//�򿪴�ת���ļ�
			FILE *infile;
			infile = fopen(argv[3], "rb");

			//�򿪽���ת�����ı����ļ�
			FILE *outfile;
			outfile = fopen(argv[4], "wb");
			//�ļ���ȡ������
			if (outfile == NULL)
			{
				fprintf(stderr, "�޷���Դ�ļ�\n");
				fclose(infile);
				return -1;
			}

			while (!feof(infile))
			{
				ch = fgetc(infile);
				if (ch == '\n')
				{
					fputc('\r', outfile);
					fputc('\n', outfile);
				}
				else fputc(ch, outfile);
			}

			fclose(infile);
			fclose(outfile);
		}

		else
		{
			fprintf(stderr, "��������\n");
			return -1;
		}

	}

	else
	{
		fprintf(stderr, "��������\n");
		return -1;
	}

	return 0;
}

int is_Windows(char *filename)
{
	char ch;
	int is_windows = 0;

	FILE *infile;
	infile = fopen(filename, "rb");

	if (infile == NULL)
	{
		fprintf(stderr, "�޷���Դ�ļ�\n");
		return -1;
	}

	while (!feof(infile))
	{
		ch = fgetc(infile);
		if (ch == '\r')
		{
			is_windows = 1;
			break;
		}
	}

	fclose(infile);
	return is_windows;
}