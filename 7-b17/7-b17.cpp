/*1751367 ��2 ����*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
using namespace std;

unsigned char str_to_int(char[]);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "������������" << endl;
		return -1;
	}
	
	char *orig_file;
	char *converted_file;

	orig_file = argv[1];
	converted_file = argv[2];

	ifstream infile(orig_file, ios::binary);
	if (!infile.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		infile.close();
		return -1;
	}

	ofstream outfile(converted_file, ios::binary);
	if (!outfile.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		infile.close();
		outfile.close();
		return -1;
	}

	//���ж�ȡԴ�ļ��е���Ϣ
	while (!infile.eof())
	{
		char ascii_str[16][3];//���ÿһ�д�Դ�ļ��ж�ȡ��ASCII��
		unsigned char ascii_int[16]; //���Դ�ļ��ж�ȡ��ascii���Ӧ������
		int count = 0; //��¼ʵ�ʵõ���ASCII����

		infile.ignore(10); //������ǰ�����ַ�λ��

		//��ȡǰ�˸�ASCII��
		for (int i = 0; i < 8; i++)
		{
			infile.getline(ascii_str[i], 3, ' ');
		}

		infile.ignore(2); //�����ָ���

		//��ȡ��˸�ASCII��
		for (int i = 8; i < 16; i++)
		{
			infile.getline(ascii_str[i], 3, ' ');
		}

		infile.ignore(22);

		//����ȡ����ASCIIת����ʮ��������д�뵽Ŀ���ļ���
		for (int i = 0; i < 16; i++)
		{
			if (ascii_str[i][0] != 0) //�ж��Ƿ������Ч����
			{
				//ת��Ϊ���ʹ�ŵ����鵱��
				ascii_int[count++] = str_to_int(ascii_str[i]); 
			}
			else break;
		}

		for (int i = 0; i < count; i++)
		{
			outfile.put(ascii_int[i]);
		}
	}

	infile.close();
	outfile.close();
	return 0;
}

//�ú������ڽ�ʮ������ascii���ַ���ת��Ϊ����
unsigned char str_to_int(char str[])
{
	int part1;
	int part2;

	if (str[1] >= 'a')
	{
		part2 = str[1] - 'a'+10;
	}
	else part2 = str[1] - '0';

	if (str[0] >= 'a')
	{
		part1 = str[0] - 'a' + 10;
	}
	else part1 = str[0] - '0';

	return part1 * 16 + part2;
}