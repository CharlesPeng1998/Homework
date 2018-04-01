/*1751367 ��2 ����*/
#include <iostream>
#include <cstdlib>
#include <cstring> 
using namespace std;

int usage(const char *procname);
bool check_no(char *no_1, char *no_2);
bool check_filename(char *filename);
bool check_threshold(char *threshold);
bool check_output(char *output);

int main(int argc, char *argv[])
{
	int threshold=80;
	
	//�����������Ƿ��㹻5��
	if (argc < 6) 
	{
		usage(argv[0]);
		return 0;
	}

	if (check_no(argv[1], argv[2]))
	{
		if (check_filename(argv[3]))
		{
			if (check_threshold(argv[4]))
			{
				threshold = atoi(argv[4]);
			}
			
			if (check_output(argv[5]))
			{
				cout << "�������ͨ��" << endl;
				cout << "���ѧ��:" << argv[1] << endl;
				cout << "ƥ��ѧ��:" << argv[2] << endl;
				cout << "Դ�ļ���:" << argv[3] << endl;
				cout << "ƥ����ֵ:" << threshold << endl;
				cout << "���Ŀ��:" << argv[5] << endl;
			}
		}
	}

	return 0;	
}

int usage(const char *procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl;
	cout << "               1759999          1759998      all          80                screen" << endl;
	cout << "               1759999          all          3-b3.cpp     75                result.txt" << endl;
	cout << "               all              all          3-b3.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

//�ú������ڼ������ѧ����Ϣ������ƥ��
bool check_no(char *no_1, char *no_2)
{
	//���ѧ�ŵļ��
	if (strcmp(no_1, "all") == 0)
	{
		//���ѧ�ź�ƥ��ѧ���Ƿ�ͬΪall�ļ��
		if (strcmp(no_2, "all") != 0)
		{
			cout << "���ѧ��Ϊall��ƥ��ѧ�ű���Ϊall" << endl;
			return 0;
		}
	}
	else
	{
		//���ѧ�ŵ�λ�����
		if (strlen(no_1) != 7)
		{
			cout << "Ҫ����ѧ�Ų���7λ" << endl;
			return 0;
		}

		//���ѧ���Ƿ�Ϊ�����ּ��
		if ((atoi(no_1) < 1000000 || atoi(no_1) > 9999999))
		{
			cout << "Ҫ����ѧ�Ų���7λ����" << endl;
			return 0;
		}
	}

	//ƥ��ѧ�ŵļ��
	if (strcmp(no_2, "all") != 0)
	{
		//ƥ��ѧ�ŵ�λ�����
		if (strlen(no_2) != 7)
		{
			cout << "Ҫƥ���ѧ�Ų���7λ" << endl;
			return 0;
		}

		//ƥ��ѧ���Ƿ�Ϊ�����ּ��
		if ((atoi(no_2) < 1000000 || atoi(no_2) > 9999999))
		{
			cout << "Ҫƥ���ѧ�Ų���7λ����" << endl;
			return 0;
		}
	}

	//���ƥ��ѧ������ѧ���Ƿ���ͬ
	if ((strcmp(no_1, "all") != 0 && strcmp(no_2, "all") != 0) && (atoi(no_1) == atoi(no_2)))
	{
		cout << "ƥ��ѧ����Ҫ���ѧ����ͬ" << endl;
		return 0;
	}

	return 1;
}

//�ú������ڼ���ļ���
bool check_filename(char *filename)
{
	if (strcmp(filename, "all") != 0)
	{
		if (strlen(filename) > 32)
		{
			cout << "Դ�����ļ���������32�ֽ�" << endl;
			return 0;
		}
	}

	return 1;
}

//�ú������ڼ�Ⲣ������ֵ
bool check_threshold(char *threshold)
{
	int threshold_value = atoi(threshold);
	if (threshold_value < 60 || threshold_value>100) return 0;
	else return 1;
}

//�ú������ڼ�������ʽ
bool check_output(char *output)
{
	if (strlen(output) > 32)
	{
		cout << "�������ļ���������32�ֽ�" << endl;
		return 0;
	}

	return 1;
}
