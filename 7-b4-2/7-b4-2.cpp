/*1751367 计2 彭健聪*/
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
	//定义三个变量临时存储文件中读取的数据
	int no;
	char name[9];
	int score;

	//定义头指针
	Student *head;

	ifstream infile;
	infile.open("list.txt", ios::in);//打开文件
	if (infile.is_open() == 0)
	{
		cout << "打开文件失败" << endl;
		return -1;
	}

	//头指针指向表头
	head = new(nothrow) Student;
	if (head == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}
	
	//读取第一行数据
	infile >> no >> name >> score;
	//表头进行二次申请
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

	//将第一行数据填入表头
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

		//进行二次申请
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

		//将数据填入结点
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
		//打印当前结点信息
		cout << *pointer_1->no << ' ' << pointer_1->name << ' ' << *pointer_1->score << endl;
		//指向下一个结点
		pointer_1 = pointer_1->next;
		
		//释放已打印的结点
		delete pointer_2->no;
		delete pointer_2->name;
		delete pointer_2->score;
		delete pointer_2;

		pointer_2 = pointer_1;

		//判断是否还存在下一个节点
		if (pointer_1 == NULL) break;
	}

	return 0;
}