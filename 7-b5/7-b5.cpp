/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std; 

struct Student
{
	int id;//报名学生的序号，抽取时使用
	int no;//报名号
	char *name;
	char *school;
	struct Student *next;
};

//该函数用于判断某个某个目标值是否存在于数组中
bool judge_exist(int target,int id[], int num);


int main()
{
	//定义两个变量来临时存储文件中读取的数据
	char name[10];
	char school[10];

	//定义头指针
	Student *head;

	//名额和报名人数
	int allow;
	int sign_up;
	
	ifstream fin;
	ofstream fout;
	fin.open("stulist.txt", ios::in);//打开文件
	fout.open("result.txt", ios::out);
	if (fin.is_open() == 0)
	{
		cout << "打开输入文件失败" << endl;
		return -1;
	}
	if (fout.is_open() == 0)
	{
		cout << "打开输出文件失败" << endl;
		fin.close();
		return -1;
	}

	fin >> allow >> sign_up;//读取名额和报名人数

    //头指针指向表头
	head = new(nothrow) Student;
	if (head == NULL)
	{
		cout << "No Memory" << endl;
		return -1;
	}

	fin >> head->no >> name >> school;

	//表头进行二次申请
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

	//将剩下的数据建立成结点
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

		//进行二次申请
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

	cout << "链表建立成功！" << endl;

	cout << allow << ' ' << sign_up << endl;

	//在报名人数中随机抽取有限名额个id
	int *select = new int[allow];
	int num = 0, random;

	srand((unsigned int)(time(0)));//生成随机种子
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

	cout << "id抽取成功" << endl;

	//从头开始遍历链表
	pointer_2 = pointer_1 = head;
	for (int i = 0; i < sign_up; i++)
	{
		if (judge_exist(pointer_1->id, select, allow))
		{
			fout << pointer_1->no << ' ' << pointer_1->name << ' '<<pointer_1->school << endl;
		}
		else;

		//指向下一个结点
		pointer_1 = pointer_1->next;

		//释放已打印的结点
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