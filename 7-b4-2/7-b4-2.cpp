/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct Student
{
	int *no;
	char *name;
	int *score;
	struct Student *next;
};

int main()
{
	//��������������ʱ�洢�ļ��ж�ȡ������
	int no;
	char name[9];
	int score;

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
		cout << "No Memory" << endl;
		return -1;
	}
	
	//��ȡ��һ������
	infile >> no >> name >> score;
	//��ͷ���ж�������
	head->no = new(nothrow) int;
	if (head->no == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}

	head->name = new(nothrow) char[strlen(name) + 1];
	if (head->name == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}

	head->score = new(nothrow) int;
	if (head->score == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}

	//����һ�����������ͷ
	*head->no = no;
	strcpy(head->name, name);
	*head->score = score;

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

		infile >> no >> name >> score;

		//���ж�������
		pointer_2->no = new(nothrow) int;
		if (pointer_2->no == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}

		pointer_2->name = new(nothrow) char[strlen(name) + 1];
		if (pointer_2->name == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}

		pointer_2->score = new(nothrow) int;
		if (pointer_2->score == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}

		//������������
		*pointer_2->no = no;
		strcpy(pointer_2->name, name);
		*pointer_2->score = score;

		if (*pointer_2->no == 9999999)
		{
			delete pointer_2;
			pointer_1->next = NULL;
			break;
		}
		else pointer_1 = pointer_2;
	}

	pointer_2 = pointer_1 = head;
	while (1)
	{
		//��ӡ��ǰ�����Ϣ
		cout << *pointer_1->no << ' ' << pointer_1->name << ' ' << *pointer_1->score << endl;
		//ָ����һ�����
		pointer_1 = pointer_1->next;
		
		//�ͷ��Ѵ�ӡ�Ľ��
		delete pointer_2->no;
		delete pointer_2->name;
		delete pointer_2->score;
		delete pointer_2;

		pointer_2 = pointer_1;

		//�ж��Ƿ񻹴�����һ���ڵ�
		if (pointer_1 == NULL) break;
	}

	return 0;
}