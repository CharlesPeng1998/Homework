/*1751367 计2 彭健聪*/
/*1750455 杨昊东 1751737 潘心那 1750034 沈一佾 1752071 马平川 1751456 石佳琛 1751988 刘昱红*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//该函数用于将十六进制ascii码字符串转化为整型
int str_to_int(char str[])
{
	int part1;
	int part2;

	if (str[1] >= 'a')
		part2 = str[1] - 'a' + 10;
	else part2 = str[1] - '0';

	if (str[0] >= 'a')
		part1 = str[0] - 'a' + 10;
	else part1 = str[0] - '0';

	return part1 * 16 + part2;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(stdout, "参数数量不足\n");
		return -1;
	}

	char *orig_file;
	char *converted_file;

	orig_file = argv[1];
	converted_file = argv[2];

	FILE *infile;
	infile = fopen(orig_file, "rb");

	if (infile == NULL)
	{
		fprintf(stderr, "文件打开失败\n");
		return -1;
	}

	FILE *outfile;
	outfile = fopen(converted_file, "wb");

	if (outfile == NULL)
	{
		fprintf(stderr, "文件打开失败\n");
		fclose(infile);
		return -1;
	}

	//逐行读取源文件中的信息
	while (!feof(infile))
	{
		char ascii_str[16][5];
		unsigned char ascii_int[16];
		int count = 0;

		fseek(infile, 10, SEEK_CUR);//跳过行前的首字符位置

									//读取前八个ASCII码
		int i;
		for (i = 0; i < 8; i++)
		{
			fgets(ascii_str[i], 4, infile);
		}

		fseek(infile, 2, SEEK_CUR);

		for (i = 8; i < 16; i++)
		{
			fgets(ascii_str[i], 4, infile);
		}

		//将读取到的ASCII转化成十六进制数写入到目标文件中
		for (i = 0; i < 16; i++)
		{
			if (ascii_str[i][0] != ' ' && ascii_str[i][1] != ' ')
			{
				ascii_int[count++] = str_to_int(ascii_str[i]);
			}
			else break;
		}

		for (i = 0; i < count; i++)
		{
			fputc(ascii_int[i], outfile);
			//printf("%d ", int(ascii_int[i]));
		}
		//printf("\n");

		fseek(infile, 21, SEEK_CUR);
		fgetc(infile);
	}

	fclose(infile);
	fclose(outfile);
	return 0;
}