/*1751367 计2 彭健聪*/
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int usage(const char *procname);
bool check_ip_address(char *ip_address);
int check_parameter(char *para_1, char *para_2, int &para_n, int &para_l, int &para_t, char *ip_address);

int main(int argc, char *argv[])
{
	//设置默认参数
	int parameter_n = 128,
		parameter_l = 100,
		parameter_t = 0;
	
	if (argc == 1)
	{
		usage(argv[0]);
		return 0;
	}

	//首先判断IP地址是否合法
	if (!check_ip_address(argv[argc - 1]))
	{
		cout << "IP地址错误" << endl;
		return 0;
	}

	//逐个参数进行检查操作
	int index = 1;
	int stat = 0;//记录check_parameter的返回值
	while (index < argc - 1)
	{
		stat=check_parameter(argv[index], argv[index + 1], parameter_n, parameter_l, parameter_t,argv[argc-1]);

		if (stat)
		{
			index += stat;
		}
		else return 0;
	}

	cout << "参数通过检查" << endl;
	cout << "-n参数:" << parameter_n << endl;
	cout << "-l参数:" << parameter_l << endl;
	cout << "-t参数:" << parameter_t << endl;
	cout << "IP地址:" << argv[argc - 1] << endl;

	return 0;
}

int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-l 大小] [-n 数量] [-t] IP地址" << endl;
	return 1;
}

//该函数用于检查IP地址是否合法
bool check_ip_address(char *ip_address)
{
	int validSegNum = 0;//记录有效片段的数量

	int seg = 0;//记录每个分段的数值
	bool segExist=0;//记录分段是否存在数值

	for (int i = 0; i < strlen(ip_address); i++)
	{
		//记录每个分段的数值
		if (ip_address[i] >= '0' && ip_address[i] <= '9')
		{
			seg = seg * 10 + (ip_address[i] - '0');
			segExist = 1;
		}
		else if (ip_address[i] == '.')
		{
			if (seg <= 255 && segExist) validSegNum++;
			else return 0;

			seg = 0;
			segExist = 0;
		}
		else return 0;
	}

	//判断最后一个分段的合法性
	if (seg <= 255 && segExist) validSegNum++;

	//判断是否有四个分段
	if (validSegNum == 4) return 1;
	else return 0;
}


/********************************
*每次接收两个字符串              *
*判断是否合法                    *
*并修改相对应的参数值              *
*********************************/
int check_parameter(char *para_1, char *para_2, int &para_n, int &para_l, int &para_t, char *ip_address)
{
	/*根据接收到的第一个字符串做不同的检查操作*/
	
	
	//根据-t后是否跟参数对参数值做出修改
	if (!strcmp(para_1, "-t"))
	{
		if (strcmp(para_2, "-l") == 0 || strcmp(para_2, "-n")==0)
		{
			para_t = 1;
		}

		return 1;
	}
	//检查-l的后续参数是否存在或者是否在合理范围
	else if (!strcmp(para_1, "-l"))
	{
		if (para_2[0] == '-' || strcmp(para_2, ip_address) == 0)
		{
			cout << "参数-l没有后续参数" << endl;
			return 0;
		}
		else if (atoi(para_2) >= 64 && atoi(para_2) <= 64000)
		{
			para_l = atoi(para_2);
		}
		else;

		return 2;
	}
	//检查-n的后续参数是否存在或者是否在合理范围
	else if (!strcmp(para_1, "-n"))
	{
		if (para_2[0] == '-'|| strcmp(para_2, ip_address) == 0)
		{
			cout << "参数-n没有后续参数" << endl;
			return 0;
		}
		else if (atoi(para_2) >= 1 && atoi(para_2) <= 10000)
		{
			para_n = atoi(para_2);
		}
		else;

		return 2;
	}
	else if (para_1[0] == '-')
	{
		cout << "参数" << para_1 << "不存在" << endl;
		return 0;
	}
	else
	{
		cout << "不是以-开头的合法参数" << endl;
		return 0;
	}
}