/*1751367 ��2 ����*/
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int usage(const char *procname);
bool check_ip_address(char *ip_address);
int check_parameter(char *para_1, char *para_2, int &para_n, int &para_l, int &para_t, char *ip_address);

int main(int argc, char *argv[])
{
	//����Ĭ�ϲ���
	int parameter_n = 128,
		parameter_l = 100,
		parameter_t = 0;
	
	if (argc == 1)
	{
		usage(argv[0]);
		return 0;
	}

	//�����ж�IP��ַ�Ƿ�Ϸ�
	if (!check_ip_address(argv[argc - 1]))
	{
		cout << "IP��ַ����" << endl;
		return 0;
	}

	//����������м�����
	int index = 1;
	int stat = 0;//��¼check_parameter�ķ���ֵ
	while (index < argc - 1)
	{
		stat=check_parameter(argv[index], argv[index + 1], parameter_n, parameter_l, parameter_t,argv[argc-1]);

		if (stat)
		{
			index += stat;
		}
		else return 0;
	}

	cout << "����ͨ�����" << endl;
	cout << "-n����:" << parameter_n << endl;
	cout << "-l����:" << parameter_l << endl;
	cout << "-t����:" << parameter_t << endl;
	cout << "IP��ַ:" << argv[argc - 1] << endl;

	return 0;
}

int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-l ��С] [-n ����] [-t] IP��ַ" << endl;
	return 1;
}

//�ú������ڼ��IP��ַ�Ƿ�Ϸ�
bool check_ip_address(char *ip_address)
{
	int validSegNum = 0;//��¼��ЧƬ�ε�����

	int seg = 0;//��¼ÿ���ֶε���ֵ
	bool segExist=0;//��¼�ֶ��Ƿ������ֵ

	for (int i = 0; i < strlen(ip_address); i++)
	{
		//��¼ÿ���ֶε���ֵ
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

	//�ж����һ���ֶεĺϷ���
	if (seg <= 255 && segExist) validSegNum++;

	//�ж��Ƿ����ĸ��ֶ�
	if (validSegNum == 4) return 1;
	else return 0;
}


/********************************
*ÿ�ν��������ַ���              *
*�ж��Ƿ�Ϸ�                    *
*���޸����Ӧ�Ĳ���ֵ              *
*********************************/
int check_parameter(char *para_1, char *para_2, int &para_n, int &para_l, int &para_t, char *ip_address)
{
	/*���ݽ��յ��ĵ�һ���ַ�������ͬ�ļ�����*/
	
	
	//����-t���Ƿ�������Բ���ֵ�����޸�
	if (!strcmp(para_1, "-t"))
	{
		if (strcmp(para_2, "-l") == 0 || strcmp(para_2, "-n")==0)
		{
			para_t = 1;
		}

		return 1;
	}
	//���-l�ĺ��������Ƿ���ڻ����Ƿ��ں���Χ
	else if (!strcmp(para_1, "-l"))
	{
		if (para_2[0] == '-' || strcmp(para_2, ip_address) == 0)
		{
			cout << "����-lû�к�������" << endl;
			return 0;
		}
		else if (atoi(para_2) >= 64 && atoi(para_2) <= 64000)
		{
			para_l = atoi(para_2);
		}
		else;

		return 2;
	}
	//���-n�ĺ��������Ƿ���ڻ����Ƿ��ں���Χ
	else if (!strcmp(para_1, "-n"))
	{
		if (para_2[0] == '-'|| strcmp(para_2, ip_address) == 0)
		{
			cout << "����-nû�к�������" << endl;
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
		cout << "����" << para_1 << "������" << endl;
		return 0;
	}
	else
	{
		cout << "������-��ͷ�ĺϷ�����" << endl;
		return 0;
	}
}