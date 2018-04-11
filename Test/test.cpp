#include <iostream>  //书上缺，要补上
#include <fstream>
#include <cstdlib>   //exit用，linux无此头文件会报错
using namespace std;

//该函数用于将十六进制ascii码字符串转化为整型
int str_to_int(char str[])
{
	int part1;
	int part2;

	if (str[1] >= 'a')
	{
		part2 = str[1] - 'a' + 10;
	}
	else part2 = str[1] - '0';

	if (str[0] >= 'a')
	{
		part1 = str[0] - 'a' + 10;
	}
	else part1 = str[0] - '0';

	return part1 * 16 + part2;
}

int main(int argc, char *argv[])
{
#if 1
	int total = 0;

	if (argc < 2)
	{
		cout << "参数数量不足" << endl;
		return -1;
	}

	char *orig_file;
	orig_file = argv[1];

	ifstream infile(orig_file, ios::in | ios::binary);
	if (!infile.is_open())
	{
		cout << "文件打开失败" << endl;
		infile.close();
		return -1;
	}
	//逐行读取源文件中的信息
	while (!infile.eof())
	{
		char ascii_str[16][3];//存放每一行从源文件中读取的ASCII码
		int ascii_int[16]; //存放源文件中读取的ascii码对应的整型
		int count = 0; //记录实际得到的ASCII数量

		infile.ignore(10); //跳过行前的首字符位置

		//读取前八个ASCII码
		for (int i = 0; i < 8; i++)
		{
			infile.getline(ascii_str[i], 3, ' ');
		}

		infile.ignore(2); //跳过分隔符

		//读取后八个ASCII码
		for (int i = 8; i < 16; i++)
		{
			infile.getline(ascii_str[i], 3, ' ');
		}

		infile.ignore(22);

		//将读取到的ASCII转化成十六进制数写入到目标文件中
		for (int i = 0; i < 16; i++)
		{
			if (ascii_str[i][0] != 0) //判断是否读到有效数据
			{
				//转化为整型存放到数组当中
				ascii_int[count++] = str_to_int(ascii_str[i]);
			}
			else break;
		}
		total += count;

		for (int i = 0; i < count; i++)
		{
			cout << ascii_int[i] << ' ';
		}
	}

	cout << endl << total << endl;
#endif

#if 0
	char text1[19][17];
	char text2[19][17];
	cin.ignore(10);
	for (int i = 0; i < 8; i++)
	{
		cin.getline(text1[i], 3, ' ');
	}

	cin.ignore(2);

	for (int i = 8; i <16; i++)
	{
		cin.getline(text1[i], 3, ' ');
	}

	for (int i = 0; i < 16; i++)
	{
		cout << text1[i]<<endl;
	}
	cout << text1[11] << endl;
	cout << text1[12] << endl;
	cout << int(text1[11][0]) << endl;
	cout << int(text1[12][0]) << endl;
	cout << int(text1[13][0]) << endl;
	cout << int(text1[14][0]) << endl;
	cout << int(text1[15][0]) << endl;


	/*cin.ignore(21);
	cout << endl;
	
	cin.ignore(10);
	for (int i = 0; i < 8; i++)
	{
		cin.getline(text2[i], 3, ' ');
	}

	cin.ignore(2);

	for (int i = 8; i <16; i++)
	{
		cin.getline(text2[i], 3, ' ');
	}

	for (int i = 0; i < 16; i++)
	{
		cout << text2[i] << endl;
	}*/
#endif	

	return 0;
}
