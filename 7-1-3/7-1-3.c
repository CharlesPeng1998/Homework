/*1751367 ��2 ����*/
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
	//�����û�����
	struct date new_date;
	struct date *p_date = &new_date;
	printf("�������꣬�£���\n");
	scanf("%d %d %d", &new_date.year, &new_date.month, &new_date.day);

	//�ж��û������Ƿ�Ϸ�
	if (new_date.year < 1)
	{
		printf("�������-��ݲ���ȷ\n");
		return 0;
	}
	else if (new_date.month < 1 || new_date.month>12)
	{
		printf("�������-�·ݲ���ȷ\n");
		return 0;
	}
	else if (days(p_date))
	{
		printf("%d-%d-%d��%d��ĵ�%d��\n", new_date.year, new_date.month, new_date.day, new_date.year, days(p_date));
		return 0;
	}
	else printf("�������-�����չ�ϵ�Ƿ�\n");

	return 0;
}

int days(struct date *new_date)
{
	int day = 0;

	//�ж��Ƿ�Ϊ����
	int leap = 0;
	if ((new_date->year % 100 != 0 && new_date->year % 4 == 0) || new_date->year % 400 == 0) leap = 1;

	//�ж����¹�ϵ�Ƿ�Ϸ�
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

	//����������չ�ϵ�Ϸ�������������㣬���򷵻�0ֵ
	if (judge)
	{
		//��ǰ���������
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
