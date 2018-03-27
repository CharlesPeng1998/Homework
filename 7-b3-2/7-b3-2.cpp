/*1751367 计2 彭健聪*/
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
		//打印当前结点信息
		cout << pointer_1->no <<' '<< pointer_1->name <<' '<< pointer_1->score << endl;
		//指向下一个结点
		pointer_1 = pointer_1->next;
		//释放已打印的结点
		delete pointer_2;

		pointer_2 = pointer_1;

		//判断是否还存在下一个节点
		if (pointer_1 == NULL) break;
	}

	return 0;
}