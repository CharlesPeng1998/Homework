/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std; 

struct Student
{
	int id;//����ѧ������ţ���ȡʱʹ��
	int no;//������
	char *name;
	char *school;
	struct Student *next;
};

//�ú��������ж�ĳ��ĳ��Ŀ��ֵ�Ƿ������������
bool judge_exist(int target,int id[], int num);


int main()
{
	//����������������ʱ�洢�ļ��ж�ȡ������
	char name[10];
	char school[10];

	//����ͷָ��
	Student *head;

	//����ͱ�������
	int allow;
	int sign_up;
	
	ifstream fin;
	ofstream fout;
	fin.open("stulist.txt", ios::in);//���ļ�
	fout.open("result.txt", ios::out);
	if (fin.is_open() == 0)
	{
		cout << "�������ļ�ʧ��" << endl;
		return -1;
	}
	if (fout.is_open() == 0)
	{
		cout << "������ļ�ʧ��" << endl;
		fin.close();
		return -1;
	}

	fin >> allow >> sign_up;//��ȡ����ͱ�������

    //ͷָ��ָ���ͷ
	head = new(nothrow) Student;
	if (head == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}

	fin >> head->no >> name >> school;

	//��ͷ���ж�������
	head->name = new(nothrow) char[strlen(name) + 1];
	if (head->name == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}
	head->school = new(nothrow) char[strlen(school) + 1];
	if (head->school == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}

	head->id = 1;
	strcpy(head->name, name);
	strcpy(head->school, school);

	Student *pointer_1 = head, *pointer_2;

	//��ʣ�µ����ݽ����ɽ��
	for (int i = 0; i < sign_up - 1; i++)
	{
		pointer_2 = new(nothrow) Student;
		if (pointer_2 == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}

		pointer_1->next = pointer_2;

		fin >> pointer_2->no >> name >> school;

		//���ж�������
		pointer_2->name = new(nothrow) char[strlen(name) + 1];
		if (pointer_2->name == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}
		pointer_2->school = new(nothrow) char[strlen(school) + 1];
		if (pointer_2->school == NULL)
		{
			cout << "No Memory" << endl;
			return -1;
		}

		pointer_2->id = i+2;
		strcpy(pointer_2->name, name);
		strcpy(pointer_2->school, school);

		pointer_1 = pointer_2;
	}

	cout << "�������ɹ���" << endl;

	cout << allow << ' ' << sign_up << endl;

	//�ڱ��������������ȡ���������id
	int *select = new int[allow];
	int num = 0, random;

	srand((unsigned int)(time(0)));//�����������
	while (num < allow)
	{
		

		random = rand() % sign_up+1;
		if (judge_exist(random, select, num)) continue;
		else
		{
			select[num] = random;
			num++;
		}
	}

	cout << "id��ȡ�ɹ�" << endl;

	//��ͷ��ʼ��������
	pointer_2 = pointer_1 = head;
	for (int i = 0; i < sign_up; i++)
	{
		if (judge_exist(pointer_1->id, select, allow))
		{
			fout << pointer_1->no << ' ' << pointer_1->name << ' '<<pointer_1->school << endl;
		}
		else;

		//ָ����һ�����
		pointer_1 = pointer_1->next;

		//�ͷ��Ѵ�ӡ�Ľ��
		delete pointer_2->name;
		delete pointer_2->school;
		delete pointer_2;

		pointer_2 = pointer_1;
	}

	fin.close();
	fout.close();

	return 0;
}

bool judge_exist(int target, int id[], int num)
{
	bool exist = 0;
	for (int i = 0; i < num; i++)
	{
		if (id[i] == target)
		{
			exist = 1;
			break;
		}
	}

	return exist;
}