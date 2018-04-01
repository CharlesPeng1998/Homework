/*1751367 计2 彭健聪*/
#include <iostream>
#include <cstdlib>
#include <cstring> 
using namespace std;

int usage(const char *procname);
bool check_no(char *no_1, char *no_2);
bool check_filename(char *filename);
bool check_threshold(char *threshold);
bool check_output(char *output);

int main(int argc, char *argv[])
{
	int threshold=80;
	
	//检查给定参数是否足够5个
	if (argc < 6) 
	{
		usage(argv[0]);
		return 0;
	}

	if (check_no(argv[1], argv[2]))
	{
		if (check_filename(argv[3]))
		{
			if (check_threshold(argv[4]))
			{
				threshold = atoi(argv[4]);
			}
			
			if (check_output(argv[5]))
			{
				cout << "参数检查通过" << endl;
				cout << "检查学号:" << argv[1] << endl;
				cout << "匹配学号:" << argv[2] << endl;
				cout << "源文件名:" << argv[3] << endl;
				cout << "匹配阈值:" << threshold << endl;
				cout << "输出目标:" << argv[5] << endl;
			}
		}
	}

	return 0;	
}

int usage(const char *procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl;
	cout << "               1759999          1759998      all          80                screen" << endl;
	cout << "               1759999          all          3-b3.cpp     75                result.txt" << endl;
	cout << "               all              all          3-b3.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

//该函数用于检查两个学号信息参数的匹配
bool check_no(char *no_1, char *no_2)
{
	//检查学号的检测
	if (strcmp(no_1, "all") == 0)
	{
		//检查学号和匹配学号是否同为all的检测
		if (strcmp(no_2, "all") != 0)
		{
			cout << "检查学号为all，匹配学号必须为all" << endl;
			return 0;
		}
	}
	else
	{
		//检查学号的位数检测
		if (strlen(no_1) != 7)
		{
			cout << "要检查的学号不是7位" << endl;
			return 0;
		}

		//检查学号是否为纯数字检测
		if ((atoi(no_1) < 1000000 || atoi(no_1) > 9999999))
		{
			cout << "要检查的学号不是7位数字" << endl;
			return 0;
		}
	}

	//匹配学号的检测
	if (strcmp(no_2, "all") != 0)
	{
		//匹配学号的位数检测
		if (strlen(no_2) != 7)
		{
			cout << "要匹配的学号不是7位" << endl;
			return 0;
		}

		//匹配学号是否为纯数字检测
		if ((atoi(no_2) < 1000000 || atoi(no_2) > 9999999))
		{
			cout << "要匹配的学号不是7位数字" << endl;
			return 0;
		}
	}

	//检测匹配学号与检查学号是否相同
	if ((strcmp(no_1, "all") != 0 && strcmp(no_2, "all") != 0) && (atoi(no_1) == atoi(no_2)))
	{
		cout << "匹配学号与要检查学号相同" << endl;
		return 0;
	}

	return 1;
}

//该函数用于检测文件名
bool check_filename(char *filename)
{
	if (strcmp(filename, "all") != 0)
	{
		if (strlen(filename) > 32)
		{
			cout << "源程序文件名超过了32字节" << endl;
			return 0;
		}
	}

	return 1;
}

//该函数用于检测并返回阈值
bool check_threshold(char *threshold)
{
	int threshold_value = atoi(threshold);
	if (threshold_value < 60 || threshold_value>100) return 0;
	else return 1;
}

//该函数用于检测输出方式
bool check_output(char *output)
{
	if (strlen(output) > 32)
	{
		cout << "输出结果文件名超过了32字节" << endl;
		return 0;
	}

	return 1;
}
