/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS		//使用了VS2017认为unsafe的函数
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstring>
using namespace std;

struct tj_time {
	int tj_year;	//表示年份
	int tj_month;	//表示月(1-12)
	int tj_day;		//表示日(1-28/29/30/31)
	int tj_hour;	//表示小时(0-23)
	int tj_minute;	//表示分(0-59)
	int tj_second;	//表示秒(0-59)
};

/* 可以在此定义其它需要的函数 */

/*该函数判断某一年是否为闰年*/
bool leap(int year)
{
	//判断是否为闰年
	bool leap = false;
	if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) leap = true;

	return leap;
}

/***************************************************************************
函数名称：
功    能：给出提示并等待回车键
输入参数：
返 回 值：
说    明：
***************************************************************************/
void wait_for_enter(const char *prompt = "")
{
	if (strlen(prompt) == 0)
		cout << endl << "按回车键继续";
	else
		cout << endl << prompt << "，按回车键继续";

	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
函数名称：
功    能：调用系统的转换函数将整型秒值转换为与本题相似的结构体并输出
输入参数：
返 回 值：
说    明：
***************************************************************************/
void system_time_output(const time_t input_time)  //time_t的本质是64位无符号整数
{
	struct tm *tt;	//struct tm 为系统定义的结构体

	tt = localtime(&input_time);	//localtime为系统函数

									/* tm_*** 为struct tm中的成员，和本题的struct tj_time具体的内容不完全符合，具体含义自己查找相关资料 */
	cout << tt->tm_year + 1900 << '-' << tt->tm_mon + 1 << '-' << tt->tm_mday << ' ' << tt->tm_hour << ':' << tt->tm_min << ':' << tt->tm_sec << endl;

	return;
}

/***************************************************************************
函数名称：
功    能：自定义转换结果输出函数
输入参数：
返 回 值：
说    明：
***************************************************************************/
void tj_time_output(struct tj_time *tp)
{
	/* 实现自定义结构的输出，输出形式与system_time_output相同 */
	cout << tp->tj_year << '-' << tp->tj_month << '-' << tp->tj_day << ' ' << tp->tj_hour << ':' << tp->tj_minute << ':' << tp->tj_second << endl;
}

/***************************************************************************
函数名称：
功    能：自定义转换函数
输入参数：
返 回 值：
说    明：
***************************************************************************/
struct tj_time *tj_time_convert(int input_time)
{
	static struct tj_time result;	//定义静态局部变量，不准动

	/* 实现过程开始，在下面添加相应的定义及执行语句即可 */
	
	//消除时区差异产生的影响
	input_time += 8 * 3600;
	
	
	//时间的初始化
	result.tj_year = 1970;
	result.tj_month = 1;
	result.tj_day = 1;
	result.tj_hour = 0;
	result.tj_minute = 0;
	result.tj_second = 0;

	//计算所给秒数经过的年份
	for (int i = 1970; ; i++)
	{
		if (leap(i) && input_time - 31622400 >= 0)
		{
			input_time -= 31622400;// 闰年的秒数
			result.tj_year += 1;
		}
		else if (!leap(i) && input_time - 31536000 >= 0)
		{
			input_time -= 31536000;//平年的秒数
			result.tj_year += 1;
		}
		else break;
	}

	//计算剩余秒数可经过的月数
	for (int i = 1; i <= 12; i++)
	{
		if (i == 1 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else if (i == 2 && leap(result.tj_year) && input_time - 29 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 29 * 86400;
		}
		else if (i == 2 && !leap(result.tj_year) && input_time - 28 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 28 * 86400;
		}
		else if (i == 3 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else if (i == 4 && input_time - 30 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 30 * 86400;
		}
		else if (i == 5 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else if (i == 6 && input_time - 30 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 30 * 86400;
		}
		else if (i == 7 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else if (i == 8 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else if (i == 9 && input_time - 30 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 30 * 86400;
		}
		else if (i == 10 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else if (i == 11 && input_time - 30 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 30 * 86400;
		}
		else if (i == 12 && input_time - 31 * 86400 >= 0)
		{
			result.tj_month++;
			input_time -= 31 * 86400;
		}
		else break;
	}

	//计算剩余秒数可经过的天数
	result.tj_day += input_time / 86400;
	input_time %= 86400;

	//计算剩余秒数可经过的小时数
	result.tj_hour += input_time / 3600;
	input_time %= 3600;

	//计算剩余秒数可经过的分钟数
	result.tj_minute += input_time / 60;
	input_time %= 60;

	//加上剩余的秒数
	result.tj_second += input_time;



	/* 实现过程结束 */

	return &result;	//注意，返回的是静态局部变量的地址，本语句不准动
}

/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：
***************************************************************************/
int main()
{
	int test_time[] = { 1, 123456789, 349823021, 987654321, 1202990407, 1216468807, 1250312143, 1272636353, 1326193524, 1336549496, 1392837128, 1625675376, 2052743737 };
	int i;
	struct tj_time *tp;

	for (i = 0; i<sizeof(test_time) / sizeof(int); i++) {
		cout << "秒数            ：" << test_time[i] << endl;
		cout << "系统转换的结果  ：";
		system_time_output(test_time[i]);

		cout << "自定义转换的结果：";
		tp = tj_time_convert(test_time[i]);
		tj_time_output(tp);

		wait_for_enter();
	}

	if (1) {
		struct tj_time *tp;
		int t = (int)time(0);		//系统函数，取当前系统时间（从1970-01-01 00:00:00开始的秒数）

		cout << "当前系统时间    ：" << t << endl;
		cout << "系统转换的结果  ：";
		system_time_output(t);

		cout << "自定义转换的结果：";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		wait_for_enter();
	}

	return 0;
}
