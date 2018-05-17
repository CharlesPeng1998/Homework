/*1751367 ��2 ����*/
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	int is_leap_year();  //�ж��Ƿ����꣬�ǣ�����1  /   �񣺷���0
public:
	int calc_days();     //�����ǵ���ĵڼ���
						 /* ������Բ���������Ҫ�����Ա�����Ķ��壬�������� */
	Days(int y, int m, int d) :year(y), month(m), day(d) {}
};

/* �˴��������Ա����������ʵ�� */
int Days::is_leap_year()
{
	//�ж��Ƿ�Ϊ����
	int leap = 0;
	if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) leap = 1;

	return leap;
}

int Days::calc_days()
{
	int total_day = 0;

	//�ж��Ƿ�Ϊ����
	int leap = is_leap_year();
	//�ж����¹�ϵ�Ƿ�Ϸ�
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

	//����������չ�ϵ�Ϸ�������������㣬���򷵻�0ֵ
	if (judge)
	{
		//��ǰ���������
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


/* main������׼�� */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "Ӧ�����78�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "Ӧ�����365��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "Ӧ�����366��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "Ӧ�����-1�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	return 0;
}
