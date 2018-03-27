/*1751367 ��2 ����*/
#include <iostream>
#include <fstream>
using namespace std;

struct Student
{
	int no;
	char name[9];
	int score;
	struct Student *next;
};

int main()
{
	//����ͷָ��
	Student *head;

	ifstream infile;
	infile.open("list.txt", ios::in);//���ļ�
	if (infile.is_open() == 0)
	{
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}

	//ͷָ��ָ���ͷ
	head = new(nothrow) Student;
	if (head == NULL)
	{
		cout<<"No Memory\n";
		return -1;
	}
	infile >> head->no >> head->name >> head->score;

	Student *pointer_1 = head, *pointer_2;

	while (1)
	{
		pointer_2 = new(nothrow) Student;
		
		if (pointer_2 == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}

		pointer_1->next = pointer_2;

		infile >> pointer_2->no >> pointer_2->name >> pointer_2->score;

		if (pointer_2->no == 9999999)
		{
			delete pointer_2;
			pointer_1->next = NULL;
			break;
		}
		else pointer_1 = pointer_2;
	}

	pointer_2=pointer_1 = head;
	while (1)
	{
		//��ӡ��ǰ�����Ϣ
		cout << pointer_1->no <<' '<< pointer_1->name <<' '<< pointer_1->score << endl;
		//ָ����һ�����
		pointer_1 = pointer_1->next;
		//�ͷ��Ѵ�ӡ�Ľ��
		delete pointer_2;

		pointer_2 = pointer_1;

		//�ж��Ƿ񻹴�����һ���ڵ�
		if (pointer_1 == NULL) break;
	}

	return 0;
}