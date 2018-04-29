/*1751367 计2 彭健聪*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int is_Windows(char *filename);

int main(int argc, char *argv[])
{
	char ch;
	
	if (argc < 3)
	{
		cout << "参数数量不足" << endl;
		return -1;
	}

	//检查命令行参数
	else if (strcmp(argv[1], "-check")==0)
	{
		int is_windows = is_Windows(argv[2]);
		switch (is_windows)
		{
		case 1:cout << "Windows格式" << endl; break;
		case 0:cout << "Linux格式" << endl; break;
		case -1:break;
		}
	}

	else if (strcmp(argv[1], "-convert")==0)
	{
		if (strcmp(argv[2], "wtol")==0)
		{
			//检查需要转换的文件是否为windows文本文件
			if (is_Windows(argv[3]) == 0)
			{
				cout << "文件格式错误" << endl;
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//打开待转换文件
			ifstream infile(argv[3], ios::in | ios::binary);

			//打开接收转化后文本的文件
			ofstream outfile(argv[4], ios::out | ios::binary);
			//文件读取错误处理
			if (!outfile.is_open())
			{
				cerr << "无法打开源文件" << endl;
				infile.close();//记得关掉		
				return -1;
			}

			while (infile.get(ch))
			{
				/*遇到UNIX文本格式的'\n'则输入
				遇到'\r'则不输入*/
				if (ch != '\r')
					outfile.put(ch);
			}

			infile.close();
			outfile.close();
		}

		else if (strcmp(argv[2], "ltow") == 0)
		{
			//检查需要转换的文件是否为linux文本文件
			if (is_Windows(argv[3]) == 1)
			{
				cout << "文件格式错误" << endl;
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//打开待转换文件
			ifstream infile(argv[3], ios::in | ios::binary);
			//文件读取错误处理
			if (!infile.is_open())
			{
				cerr << "无法打开源文件" << endl;
				infile.close();//记得关掉			
				return -1;
			}

			//打开接收转化后文本的文件
			ofstream outfile(argv[4], ios::out | ios::binary);
			//文件读取错误处理
			if (!outfile.is_open())
			{
				cerr << "无法打开源文件" << endl;
				infile.close();//记得关掉			
				return -1;
			}

			while (infile.get(ch))
			{
				if (ch == '\n')
				{
					outfile.put('\r');
					outfile.put(ch);
				}
				else outfile.put(ch);
			}

			infile.close();
			outfile.close();
		}

		else
		{
			cout << "参数错误" << endl;
			return -1;
		}
	}

	else
	{
		cout << "参数错误" << endl;
		return -1;
	}

	return 0;
}

int is_Windows(char *filename)
{
	char ch;//读取文件时需要用到的字符变量
	int is_windows = 0;
	
	//根据命令行参数读入文件
	ifstream infile(filename, ios::in | ios::binary);
	//文件读取错误处理
	if (!infile.is_open())
	{
		cerr << "无法打开源文件" << endl;			
		return -1;
	}
	
	//逐个字符检查是否存在windows下的换行符\r
	while (!infile.eof())
	{
		ch = infile.get();
		if (ch == '\r')
		{	
			is_windows = 1;
			break;
		}
	}

	infile.close();//记得关闭文件
	return is_windows;
}