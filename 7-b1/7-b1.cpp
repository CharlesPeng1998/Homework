/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS		//ʹ����VS2017��Ϊunsafe�ĺ���
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstring>
using namespace std;

struct tj_time {
	int tj_year;	//��ʾ���
	int tj_month;	//��ʾ��(1-12)
	int tj_day;		//��ʾ��(1-28/29/30/31)
	int tj_hour;	//��ʾСʱ(0-23)
	int tj_minute;	//��ʾ��(0-59)
	int tj_second;	//��ʾ��(0-59)
};

/* �����ڴ˶���������Ҫ�ĺ��� */

/*�ú����ж�ĳһ���Ƿ�Ϊ����*/
bool leap(int year)
{
	//�ж��Ƿ�Ϊ����
	bool leap = false;
	if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) leap = true;

	return leap;
}

/***************************************************************************
�������ƣ�
��    �ܣ�������ʾ���ȴ��س���
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void wait_for_enter(const char *prompt = "")
{
	if (strlen(prompt) == 0)
		cout << endl << "���س�������";
	else
		cout << endl << prompt << "�����س�������";

	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
�������ƣ�
��    �ܣ�����ϵͳ��ת��������������ֵת��Ϊ�뱾�����ƵĽṹ�岢���
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void system_time_output(const time_t input_time)  //time_t�ı�����64λ�޷�������
{
	struct tm *tt;	//struct tm Ϊϵͳ����Ľṹ��

	tt = localtime(&input_time);	//localtimeΪϵͳ����

									/* tm_*** Ϊstruct tm�еĳ�Ա���ͱ����struct tj_time��������ݲ���ȫ���ϣ����庬���Լ������������ */
	cout << tt->tm_year + 1900 << '-' << tt->tm_mon + 1 << '-' << tt->tm_mday << ' ' << tt->tm_hour << ':' << tt->tm_min << ':' << tt->tm_sec << endl;

	return;
}

/***************************************************************************
�������ƣ�
��    �ܣ��Զ���ת������������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void tj_time_output(struct tj_time *tp)
{
	/* ʵ���Զ���ṹ������������ʽ��system_time_output��ͬ */
	cout << tp->tj_year << '-' << tp->tj_month << '-' << tp->tj_day << ' ' << tp->tj_hour << ':' << tp->tj_minute << ':' << tp->tj_second << endl;
}

/***************************************************************************
�������ƣ�
��    �ܣ��Զ���ת������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
struct tj_time *tj_time_convert(int input_time)
{
	static struct tj_time result;	//���徲̬�ֲ���������׼��

	/* ʵ�ֹ��̿�ʼ�������������Ӧ�Ķ��弰ִ����伴�� */
	
	//����ʱ�����������Ӱ��
	input_time += 8 * 3600;
	
	
	//ʱ��ĳ�ʼ��
	result.tj_year = 1970;
	result.tj_month = 1;
	result.tj_day = 1;
	result.tj_hour = 0;
	result.tj_minute = 0;
	result.tj_second = 0;

	//���������������������
	for (int i = 1970; ; i++)
	{
		if (leap(i) && input_time - 31622400 >= 0)
		{
			input_time -= 31622400;// ���������
			result.tj_year += 1;
		}
		else if (!leap(i) && input_time - 31536000 >= 0)
		{
			input_time -= 31536000;//ƽ�������
			result.tj_year += 1;
		}
		else break;
	}

	//����ʣ�������ɾ���������
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

	//����ʣ�������ɾ���������
	result.tj_day += input_time / 86400;
	input_time %= 86400;

	//����ʣ�������ɾ�����Сʱ��
	result.tj_hour += input_time / 3600;
	input_time %= 3600;

	//����ʣ�������ɾ����ķ�����
	result.tj_minute += input_time / 60;
	input_time %= 60;

	//����ʣ�������
	result.tj_second += input_time;



	/* ʵ�ֹ��̽��� */

	return &result;	//ע�⣬���ص��Ǿ�̬�ֲ������ĵ�ַ������䲻׼��
}

/***************************************************************************
�������ƣ�
��    �ܣ�
���������
�� �� ֵ��
˵    ����
***************************************************************************/
int main()
{
	int test_time[] = { 1, 123456789, 349823021, 987654321, 1202990407, 1216468807, 1250312143, 1272636353, 1326193524, 1336549496, 1392837128, 1625675376, 2052743737 };
	int i;
	struct tj_time *tp;

	for (i = 0; i<sizeof(test_time) / sizeof(int); i++) {
		cout << "����            ��" << test_time[i] << endl;
		cout << "ϵͳת���Ľ��  ��";
		system_time_output(test_time[i]);

		cout << "�Զ���ת���Ľ����";
		tp = tj_time_convert(test_time[i]);
		tj_time_output(tp);

		wait_for_enter();
	}

	if (1) {
		struct tj_time *tp;
		int t = (int)time(0);		//ϵͳ������ȡ��ǰϵͳʱ�䣨��1970-01-01 00:00:00��ʼ��������

		cout << "��ǰϵͳʱ��    ��" << t << endl;
		cout << "ϵͳת���Ľ��  ��";
		system_time_output(t);

		cout << "�Զ���ת���Ľ����";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		wait_for_enter();
	}

	return 0;
}
