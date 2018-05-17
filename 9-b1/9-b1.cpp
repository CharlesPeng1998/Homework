/*1751367 计2 彭健聪*/
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	int is_leap_year();  //判断是否闰年，是：返回1  /   否：返回0
public:
	int calc_days();     //计算是当年的第几天
						 /* 下面可以补充其它需要的类成员函数的定义，数量不限 */
	Days(int y, int m, int d) :year(y), month(m), day(d) {}
};

/* 此处给出类成员函数的体外实现 */
int Days::is_leap_year()
{
	//判断是否为闰年
	int leap = 0;
	if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) leap = 1;

	return leap;
}

int Days::calc_days()
{
	int total_day = 0;

	//判断是否为闰年
	int leap = is_leap_year();
	//判断年月关系是否合法
	int judge = 1;
	switch (month)
	{
	case 1:if (day < 1 || day>31) judge = 0;
	case 2:
	{
		if (leap)
		{
			if (day < 1 || day>29) judge = 0;
		}
		else
		{
			if (day < 1 || day>28) judge = 0;
		}

	}
	case 3:if (day < 1 || day>31) judge = 0;
	case 4:if (day < 1 || day>30) judge = 0;
	case 5:if (day < 1 || day>31) judge = 0;
	case 6:if (day < 1 || day>30) judge = 0;
	case 7:if (day < 1 || day>31) judge = 0;
	case 8:if (day < 1 || day>31) judge = 0;
	case 9:if (day < 1 || day>30) judge = 0;
	case 10:if (day < 1 || day>31) judge = 0;
	case 11:if (day < 1 || day>30) judge = 0;
	case 12:if (day < 1 || day>31) judge = 0;
	}

	//若输入的月日关系合法则进行天数计算，否则返回0值
	if (judge)
	{
		//将前月天数相加
		int i = 1;
		for (i = 1; i < month; i++)
		{
			switch (i)
			{
			case 1:total_day += 31; break;
			case 2:
			{
				if (leap) day += 29;
				else day += 28;
				break;
			}
			case 3:total_day += 31; break;
			case 4:total_day += 30; break;
			case 5:total_day += 31; break;
			case 6:total_day += 30; break;
			case 7:total_day += 31; break;
			case 8:total_day += 31; break;
			case 9:total_day += 30; break;
			case 10:total_day += 31; break;
			case 11:total_day += 30; break;
			}
		}
		total_day += day;
		return total_day;
	}
	else return -1;
}


/* main函数不准动 */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "应该输出78， 实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "应该输出365，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "应该输出366，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "应该输出-1， 实际是：" << d1.calc_days() << endl;
	}

	return 0;
}
