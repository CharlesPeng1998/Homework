/*1751367 ��2 ����*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int is_Windows(char *filename);

int main(int argc, char *argv[])
{
	char ch;
	
	if (argc < 3)
	{
		cout << "������������" << endl;
		return -1;
	}

	//��������в���
	else if (strcmp(argv[1], "-check")==0)
	{
		int is_windows = is_Windows(argv[2]);
		switch (is_windows)
		{
		case 1:cout << "Windows��ʽ" << endl; break;
		case 0:cout << "Linux��ʽ" << endl; break;
		case -1:break;
		}
	}

	else if (strcmp(argv[1], "-convert")==0)
	{
		if (strcmp(argv[2], "wtol")==0)
		{
			//�����Ҫת�����ļ��Ƿ�Ϊwindows�ı��ļ�
			if (is_Windows(argv[3]) == 0)
			{
				cout << "�ļ���ʽ����" << endl;
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//�򿪴�ת���ļ�
			ifstream infile(argv[3], ios::in | ios::binary);

			//�򿪽���ת�����ı����ļ�
			ofstream outfile(argv[4], ios::out | ios::binary);
			//�ļ���ȡ������
			if (!outfile.is_open())
			{
				cerr << "�޷���Դ�ļ�" << endl;
				infile.close();//�ǵùص�		
				return -1;
			}

			while (infile.get(ch))
			{
				/*����UNIX�ı���ʽ��'\n'������
				����'\r'������*/
				if (ch != '\r')
					outfile.put(ch);
			}

			infile.close();
			outfile.close();
		}

		else if (strcmp(argv[2], "ltow") == 0)
		{
			//�����Ҫת�����ļ��Ƿ�Ϊlinux�ı��ļ�
			if (is_Windows(argv[3]) == 1)
			{
				cout << "�ļ���ʽ����" << endl;
				return -1;
			}
			else if (is_Windows(argv[3]) == -1)
				return -1;

			//�򿪴�ת���ļ�
			ifstream infile(argv[3], ios::in | ios::binary);
			//�ļ���ȡ������
			if (!infile.is_open())
			{
				cerr << "�޷���Դ�ļ�" << endl;
				infile.close();//�ǵùص�			
				return -1;
			}

			//�򿪽���ת�����ı����ļ�
			ofstream outfile(argv[4], ios::out | ios::binary);
			//�ļ���ȡ������
			if (!outfile.is_open())
			{
				cerr << "�޷���Դ�ļ�" << endl;
				infile.close();//�ǵùص�			
				return -1;
			}

			while (infile.get(ch))
			{
				if (ch == '\n')
				{
					outfile.put('\r');
					outfile.put(ch);
				}
				else outfile.put(ch);
			}

			infile.close();
			outfile.close();
		}

		else
		{
			cout << "��������" << endl;
			return -1;
		}
	}

	else
	{
		cout << "��������" << endl;
		return -1;
	}

	return 0;
}

int is_Windows(char *filename)
{
	char ch;//��ȡ�ļ�ʱ��Ҫ�õ����ַ�����
	int is_windows = 0;
	
	//���������в��������ļ�
	ifstream infile(filename, ios::in | ios::binary);
	//�ļ���ȡ������
	if (!infile.is_open())
	{
		cerr << "�޷���Դ�ļ�" << endl;			
		return -1;
	}
	
	//����ַ�����Ƿ����windows�µĻ��з�\r
	while (!infile.eof())
	{
		ch = infile.get();
		if (ch == '\r')
		{	
			is_windows = 1;
			break;
		}
	}

	infile.close();//�ǵùر��ļ�
	return is_windows;
}