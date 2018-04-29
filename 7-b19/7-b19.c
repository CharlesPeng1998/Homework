/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int is_Windows(char *filename);

int main(int argc,char *argv[])
{
	char ch;

	if (argc < 3)
	{
		fprintf(stdout, "参数数量不足\n");
		return -1;
	}

	//检查命令行参数
	else if (strcmp(argv[1], "-check") == 0)
	{
		int is_windows = is_Windows(argv[2]);
		switch (is_windows)
		{
			case 1:fprintf(stdout, "Windows格式\n"); break;
			case 0:fprintf(stdout, "Linux格式\n"); break;
			case -1:break;
		}
	}

	else if (strcmp(argv[1], "-convert") == 0)
	{
		if (strcmp(argv[2], "wtol") == 0)
		{
			//检查需要转换的文件是否为windows文本文件
			if (is_Windows(argv[3]) == 0)
			{
				fprintf(stdout, "文件格式错误\n");
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//打开待转换的文件
			FILE *infile;
			infile = fopen(argv[3], "rb");

			//打开接收转化后文本的文件
			FILE *outfile;
			outfile = fopen(argv[4], "wb");
			//文件读取错误处理
			if (outfile == NULL)
			{
				fprintf(stderr, "无法打开文件\n");
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
			//检查需要转换的文件是否为linux文本文件
			if (is_Windows(argv[3]) == 1)
			{
				fprintf(stdout, "文件格式错误\n");
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//打开待转换文件
			FILE *infile;
			infile = fopen(argv[3], "rb");

			//打开接收转化后文本的文件
			FILE *outfile;
			outfile = fopen(argv[4], "wb");
			//文件读取错误处理
			if (outfile == NULL)
			{
				fprintf(stderr, "无法打开源文件\n");
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
			fprintf(stderr, "参数错误\n");
			return -1;
		}

	}

	else
	{
		fprintf(stderr, "参数错误\n");
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
		fprintf(stderr, "无法打开源文件\n");
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