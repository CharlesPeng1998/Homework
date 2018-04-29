/*1751367 计2 彭健聪*/
/*1750455 杨昊东 1751737 潘心那 1750034 沈一佾 1752071 马平川 1751456 石佳琛 1751988 刘昱红*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	char *filename = (char *)malloc(50);
	char ch;

	//检查是否带有命令行参数
	if (argc > 1)
		filename = argv[1];
	else
	{
		char input_filename[50];//接收用户输入的文件名
		fprintf(stdout, "文件名以下形式均可以：\n");
		fprintf(stdout, "    a.txt：不带路径形式\n");
		fprintf(stdout, "    ..\\data\\b.dat：相对路径形式\n");
		fprintf(stdout, "    C:\\Windows\\System32\\c.dat：绝对相对路径形式\n");
		fprintf(stdout, "请输入文件名：");
		scanf("%s", input_filename);

		strcpy(filename, input_filename);
	}

	FILE *infile;
	infile = fopen(filename, "rb");
	//错误处理
	if (infile == NULL)
	{
		fprintf(stderr, "文件打开失败\n");
		return -1;
	}

	int curr_pos = 0;//记录当行首字符的位置

	while (!feof(infile))
	{
		char curr_line[17];//记录当行的字符
		int curr_line_ascii[16] = { 0 };//记录当行每个字符的ASCII值

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
			else //文件结束时会多读一个，因此退一
			{
				count--;
				break;
			}
		}

		curr_line[count] = '\0'; //当行字符串添加尾0

		//打印每行
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