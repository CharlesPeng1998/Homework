#include <iostream>  //����ȱ��Ҫ����
#include <fstream>
#include <cstdlib>   //exit�ã�linux�޴�ͷ�ļ��ᱨ��
using namespace std;

//�ú������ڽ�ʮ������ascii���ַ���ת��Ϊ����
int str_to_int(char str[])
{
	int part1;
	int part2;

	if (str[1] >= 'a')
	{
		part2 = str[1] - 'a' + 10;
	}
	else part2 = str[1] - '0';

	if (str[0] >= 'a')
	{
		part1 = str[0] - 'a' + 10;
	}
	else part1 = str[0] - '0';

	return part1 * 16 + part2;
}

int main(int argc, char *argv[])
{
#if 1
	int total = 0;

	if (argc < 2)
	{
		cout << "������������" << endl;
		return -1;
	}

	char *orig_file;
	orig_file = argv[1];

	ifstream infile(orig_file, ios::in | ios::binary);
	if (!infile.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		infile.close();
		return -1;
	}
	//���ж�ȡԴ�ļ��е���Ϣ
	while (!infile.eof())
	{
		char ascii_str[16][3];//���ÿһ�д�Դ�ļ��ж�ȡ��ASCII��
		int ascii_int[16]; //���Դ�ļ��ж�ȡ��ascii���Ӧ������
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
		total += count;

		for (int i = 0; i < count; i++)
		{
			cout << ascii_int[i] << ' ';
		}
	}

	cout << endl << total << endl;
#endif

#if 0
	char text1[19][17];
	char text2[19][17];
	cin.ignore(10);
	for (int i = 0; i < 8; i++)
	{
		cin.getline(text1[i], 3, ' ');
	}

	cin.ignore(2);

	for (int i = 8; i <16; i++)
	{
		cin.getline(text1[i], 3, ' ');
	}

	for (int i = 0; i < 16; i++)
	{
		cout << text1[i]<<endl;
	}
	cout << text1[11] << endl;
	cout << text1[12] << endl;
	cout << int(text1[11][0]) << endl;
	cout << int(text1[12][0]) << endl;
	cout << int(text1[13][0]) << endl;
	cout << int(text1[14][0]) << endl;
	cout << int(text1[15][0]) << endl;


	/*cin.ignore(21);
	cout << endl;
	
	cin.ignore(10);
	for (int i = 0; i < 8; i++)
	{
		cin.getline(text2[i], 3, ' ');
	}

	cin.ignore(2);

	for (int i = 8; i <16; i++)
	{
		cin.getline(text2[i], 3, ' ');
	}

	for (int i = 0; i < 16; i++)
	{
		cout << text2[i] << endl;
	}*/
#endif	

	return 0;
}
