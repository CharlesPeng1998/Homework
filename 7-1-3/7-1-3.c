/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

struct date
{
	int year;
	int month;
	int day;
};

int days(struct date*);

int main()
{
	//接收用户输入
	struct date new_date;
	struct date *p_date = &new_date;
	printf("请输入年，月，日\n");
	scanf("%d %d %d", &new_date.year, &new_date.month, &new_date.day);

	//判断用户输入是否合法
	if (new_date.year < 1)
	{
		printf("输入错误-年份不正确\n");
		return 0;
	}
	else if (new_date.month < 1 || new_date.month>12)
	{
		printf("输入错误-月份不正确\n");
		return 0;
	}
	else if (days(p_date))
	{
		printf("%d-%d-%d是%d年的第%d天\n", new_date.year, new_date.month, new_date.day, new_date.year, days(p_date));
		return 0;
	}
	else printf("输入错误-月与日关系非法\n");

	return 0;
}

int days(struct date *new_date)
{
	int day = 0;

	//判断是否为闰年
	int leap = 0;
	if ((new_date->year % 100 != 0 && new_date->year % 4 == 0) || new_date->year % 400 == 0) leap = 1;

	//判断年月关系是否合法
	int judge = 1;
	switch (new_date->month)
	{
	case 1:if (new_date->day < 1 || new_date->day>31) judge = 0;
	case 2:
	{
		if (leap)
		{
			if (new_date->day < 1 || new_date->day>29) judge = 0;
		}
		else
		{
			if (new_date->day < 1 || new_date->day>28) judge = 0;
		}

	}
	case 3:if (new_date->day < 1 || new_date->day>31) judge = 0;
	case 4:if (new_date->day < 1 || new_date->day>30) judge = 0;
	case 5:if (new_date->day < 1 || new_date->day>31) judge = 0;
	case 6:if (new_date->day < 1 || new_date->day>30) judge = 0;
	case 7:if (new_date->day < 1 || new_date->day>31) judge = 0;
	case 8:if (new_date->day < 1 || new_date->day>31) judge = 0;
	case 9:if (new_date->day < 1 || new_date->day>30) judge = 0;
	case 10:if (new_date->day < 1 || new_date->day>31) judge = 0;
	case 11:if (new_date->day < 1 || new_date->day>30) judge = 0;
	case 12:if (new_date->day < 1 || new_date->day>31) judge = 0;
	}

	//若输入的月日关系合法则进行天数计算，否则返回0值
	if (judge)
	{
		//将前月天数相加
		int i = 1;
		for (i = 1; i < new_date->month; i++)
		{
			switch (i)
			{
			case 1:day += 31; break;
			case 2:
			{
				if (leap) day += 29;
				else day += 28;
				break;
			}
			case 3:day += 31; break;
			case 4:day += 30; break;
			case 5:day += 31; break;
			case 6:day += 30; break;
			case 7:day += 31; break;
			case 8:day += 31; break;
			case 9:day += 30; break;
			case 10:day += 31; break;
			case 11:day += 30; break;
			}
		}
		day += new_date->day;
		return day;
	}
	else return 0;
}
