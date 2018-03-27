/* 1751367 ��2 ����*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */
#include <ctime>
using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */
#define HEART 3
#define DIAMOND 4
#define CLU 5
#define SPADE 6

/* ��������Լ���Ҫ�ĺ��� */

/* ��ӡĳ����ҵ�������Ϣ������ǵ���������ӱ�� */
int print(const char *prompt, const int landlord, const unsigned long long player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	unsigned long long card = player;
	
	
	cout << prompt;

	/*��64λ������ǰ��ʮ��λ�ֳ�ʮ���ݣ��ֱ����ͬ��������ֵ
	ÿ���е���λ�ɵ�λ����λ�ֱ����C D H S���ֻ�ɫ*/
	for (int i = 3; i < 16; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			/*�ӵ�λ��ʼ��λ��飬��ֵΪ1����ƴ��ڣ�
			��ӡ���������λ���㣬�Ա��ڼ����һλ*/
			if (card & 1)
			{
				switch (j)
				{
				case 0:cout << char(CLU); break;
				case 1:cout << char(DIAMOND); break;
				case 2:cout << char(HEART); break;
				case 3:cout << char(SPADE); break;
				}

				switch (i)
				{
				case 10:cout << 'T'; break;
				case 11:cout << 'J'; break;
				case 12:cout << 'Q'; break;
				case 13:cout << 'K'; break;
				case 14:cout << 'A'; break;
				case 15:cout << 2; break;
				default:cout << i; break;
				}
				cout << ' ';	
			}

			card = card >> 1;
		}
	}

	//����Ƿ���С��������
	if (card & 1) cout << "BJ ";
	card = card >> 1;
	if (card & 1) cout << "RJ ";

	//�������Ϊ�����������ӡ����
	if (landlord) cout << "<����>";

	cout << endl;

	return 0;
}

int deal(unsigned long long *player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	int random;//�����
	int landlord;

	/*���ڷ��Ƶ��ƶѣ�ĳλΪ1˵�������Դ������ƶ���,
	              �����ѱ��ַ���ȥ*/
	unsigned long long orig_card = 0xFFFFFFFFFFFFFFFF;

	srand((unsigned int)(time(0)));

	for (int i = 0; i < 17; i++)
	{
		//������Ƹ������
		while (1)
		{
			random = rand() % 54;
			//�����������Ƿ��Ѿ��ַ���ȥ
			if (orig_card & (unsigned long long)(pow(2, random)))
			{
				orig_card -= (unsigned long long)(pow(2, random));
				player[0] += (unsigned long long)(pow(2, random));
				break;
			}
			else continue;
		}

		//������Ƹ������
		while (1)
		{
			random = rand() % 54;
			//�����������Ƿ��Ѿ��ַ���ȥ
			if (orig_card & (unsigned long long)(pow(2, random)))
			{
				orig_card -= (unsigned long long)(pow(2, random));
				player[1] += (unsigned long long)(pow(2, random));
				break;
			}
			else continue;
		}

		//������Ƹ������
		while (1)
		{
			random = rand() % 54;
			//�����������Ƿ��Ѿ��ַ���ȥ
			if (orig_card & (unsigned long long)(pow(2, random)))
			{
				orig_card -= (unsigned long long)(pow(2, random));
				player[2] += (unsigned long long)(pow(2, random));
				break;
			}
			else continue;
		}

		cout << "��" << i + 1 << "�ֽ�����" << endl;
		
		print("�׵��ƣ�", 0, player[0]);
		print("�ҵ��ƣ�", 0, player[1]);
		print("�����ƣ�", 0, player[2]);
	}

	while (1)
	{
		cout << endl << "��ѡ��һ������[0-2]:";
		cin >> landlord;

		if (cin.fail() || landlord<0 || landlord >2)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			continue;
		}
		else break;
	}

	player[landlord] += orig_card;//��ʣ����Ƹ�����

	return landlord;
}

/* main��������׼�޸� */
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", landlord == 0, player[0]);
	print("�ҵ��ƣ�", landlord == 1, player[1]);
	print("�����ƣ�", landlord == 2, player[2]);

	return 0;
}
