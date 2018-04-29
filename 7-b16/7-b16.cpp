/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
	char *filename=new char[50]; //打开的文件名
	char ch;

	//检查是否带有命令行参数
	if (argc > 1)
		filename = argv[1];
	else
	{
		char input_filename[50]; //接收用户输入的文件名
		cout << "文件名以下形式均可以：" << endl;
		cout << "    a.txt：不带路径形式" << endl;
		cout << "    ..\\data\\b.dat：相对路径形式" << endl;
		cout << "    C:\\Windows\\System32\\c.dat：绝对相对路径形式" << endl;
		cout << "请输入文件名：";
		cin >> input_filename;

		strcpy(filename, input_filename);
	}

	ifstream infile(filename, ios::in | ios::binary);
	//错误处理
	if (!infile.is_open())
	{
		cerr << "文件打开失败" << endl;
		return -1;
	}

	int curr_pos = 0; //记录当行首字符的位置
	
	while (!infile.eof())
	{
		char curr_line[17]; //记录当行的字符
		int curr_line_ascii[16] = { 0 }; //记录当行每个字符的ASCII值

		int count;
		for (count = 0; count < 16; count++)
		{
			if (!infile.eof())
			{
				infile.get(ch);
			
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
			
			/*if ((ch=infile.get())!=EOF)
			{
				if (ch>=33 && ch<=126)
					curr_line[count] = ch;
				else curr_line[count] = '.';

				curr_line_ascii[count] = (int)(unsigned char)(ch);
			}
			else break;*/
		}

		curr_line[count] = '\0'; //当行字符串添加尾0

		//打印每行
		cout << setw(8) <<setfill('0')<< hex << curr_pos<<"  ";

		if (count > 8)
		{
			for (int i = 0; i < 8; i++)
			{
				cout << setw(2) << setfill('0') << hex << curr_line_ascii[i] << ' ';
			}

			cout << "- ";//打印八个字符后打印分隔符号

			for (int i = 8; i < count; i++)
			{
				cout << setw(2) << setfill('0') << hex << curr_line_ascii[i] << ' ';
			}

			for (int i = count; i < 16; i++)
			{
				cout << "   ";
			}
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				cout << setw(2) << setfill('0') << hex << curr_line_ascii[i] << ' ';
			}

			for (int i = count; i < 8; i++)
			{
				cout << "   ";
			}

			cout << "  ";

			for (int i = 8; i < 16; i++)
			{
				cout << "   ";
			}
		}

		cout << "    " << curr_line << endl;
		curr_pos += 16;
	}

	infile.close();
	return 0;
}