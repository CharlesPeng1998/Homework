/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
	char *filename=new char[50]; //�򿪵��ļ���
	char ch;

	//����Ƿ���������в���
	if (argc > 1)
		filename = argv[1];
	else
	{
		char input_filename[50]; //�����û�������ļ���
		cout << "�ļ���������ʽ�����ԣ�" << endl;
		cout << "    a.txt������·����ʽ" << endl;
		cout << "    ..\\data\\b.dat�����·����ʽ" << endl;
		cout << "    C:\\Windows\\System32\\c.dat���������·����ʽ" << endl;
		cout << "�������ļ�����";
		cin >> input_filename;

		strcpy(filename, input_filename);
	}

	ifstream infile(filename, ios::in | ios::binary);
	//������
	if (!infile.is_open())
	{
		cerr << "�ļ���ʧ��" << endl;
		return -1;
	}

	int curr_pos = 0; //��¼�������ַ���λ��
	
	while (!infile.eof())
	{
		char curr_line[17]; //��¼���е��ַ�
		int curr_line_ascii[16] = { 0 }; //��¼����ÿ���ַ���ASCIIֵ

		int count;
		for (count = 0; count < 16; count++)
		{
			if (!infile.eof())
			{
				infile.get(ch);
			
				if (ch >= 33 && ch <= 126)
					curr_line[count] = ch;
				else curr_line[count] = '.';

				curr_line_ascii[count] = (int)(unsigned char)(ch);
			}
			else //�ļ�����ʱ����һ���������һ
			{
				count--;
				break;
			}
			
			/*if ((ch=infile.get())!=EOF)
			{
				if (ch>=33 && ch<=126)
					curr_line[count] = ch;
				else curr_line[count] = '.';

				curr_line_ascii[count] = (int)(unsigned char)(ch);
			}
			else break;*/
		}

		curr_line[count] = '\0'; //�����ַ������β0

		//��ӡÿ��
		cout << setw(8) <<setfill('0')<< hex << curr_pos<<"  ";

		if (count > 8)
		{
			for (int i = 0; i < 8; i++)
			{
				cout << setw(2) << setfill('0') << hex << curr_line_ascii[i] << ' ';
			}

			cout << "- ";//��ӡ�˸��ַ����ӡ�ָ�����

			for (int i = 8; i < count; i++)
			{
				cout << setw(2) << setfill('0') << hex << curr_line_ascii[i] << ' ';
			}

			for (int i = count; i < 16; i++)
			{
				cout << "   ";
			}
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				cout << setw(2) << setfill('0') << hex << curr_line_ascii[i] << ' ';
			}

			for (int i = count; i < 8; i++)
			{
				cout << "   ";
			}

			cout << "  ";

			for (int i = 8; i < 16; i++)
			{
				cout << "   ";
			}
		}

		cout << "    " << curr_line << endl;
		curr_pos += 16;
	}

	infile.close();
	return 0;
}