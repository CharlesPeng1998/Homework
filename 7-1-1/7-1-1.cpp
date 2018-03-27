/*1751367 ��2 ����*/
#include <iostream>
using namespace std;

struct date
{
	int year;
	int month;
	int day;
};

int main()
{
	int day=0;//��¼��������ڼ���
	
	//�����û�����
	date new_date;
	cout << "�������꣬�£���" << endl;
	cin >> new_date.year >> new_date.month >> new_date.day;

	//�ж��Ƿ�Ϊ����
	bool leap = false;
	if ((new_date.year % 100 != 0 && new_date.year % 4 == 0) || new_date.year % 400 == 0) leap = true;

	//�ж����¹�ϵ�Ƿ�Ϸ�
	bool judge = true;
	switch(new_date.month)
	{
	case 1:if (new_date.day < 1 || new_date.day>31) judge = false;
	case 2:
	{
		if (leap)
		{
			if (new_date.day < 1 || new_date.day>29) judge = false;
		}
		else
		{
			if (new_date.day < 1 || new_date.day>28) judge = false;
		}

	}
	case 3:if (new_date.day < 1 || new_date.day>31) judge = false;
	case 4:if (new_date.day < 1 || new_date.day>30) judge = false;
	case 5:if (new_date.day < 1 || new_date.day>31) judge = false;
	case 6:if (new_date.day < 1 || new_date.day>30) judge = false;
	case 7:if (new_date.day < 1 || new_date.day>31) judge = false;
	case 8:if (new_date.day < 1 || new_date.day>31) judge = false;
	case 9:if (new_date.day < 1 || new_date.day>30) judge = false;
	case 10:if (new_date.day < 1 || new_date.day>31) judge = false;
	case 11:if (new_date.day < 1 || new_date.day>30) judge = false;
	case 12:if (new_date.day < 1 || new_date.day>31) judge = false;
	}

	//�ж��û������Ƿ�Ϸ�
	if (new_date.year < 1)
	{
		cout << "�������-��ݲ���ȷ" << endl;
		return 0;
	}
	else if (new_date.month < 1 || new_date.month>12)
	{
		cout << "�������-�·ݲ���ȷ" << endl;
		return 0;
	}
	else if (!judge)
	{
		cout << "�������-�����չ�ϵ�Ƿ�" << endl;
		return 0;
	}

	//��ǰ���������
	for (int i = 1; i < new_date.month; i++)
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

	day += new_date.day;

	cout << new_date.year << '-' << new_date.month << '-' << new_date.day << "��" << new_date.year << "��ĵ�" << day << "��" << endl;
	return 0;
}