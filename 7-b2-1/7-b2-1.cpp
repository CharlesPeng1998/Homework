/*1751367 计2 彭健聪*/
#include <iostream>
#include <fstream>
using namespace std;

//定义一个学生结构体
struct Student
{
	int id;
	char name[7];
	int grade;
	int rank;
};

void sort_grade(Student[], int);
void sort_id(Student[], int);

int main()
{
	int student_num;//学生总人数
	Student *student_list = new(nothrow) Student[80];
	

	//若申请动态空间失败则报错并退出
	if (student_list == NULL)
	{
		cout << "No Memory";
		return -1;
	}

	ifstream infile;
	infile.open("student.txt", ios::in);//打开文件
	if (infile.is_open() == 0)
	{
		cout << "打开文件失败" << endl;
		return -1;
	}

	infile >> student_num;//读取文件第一行的学生总人数

	for (int i = 0; i < student_num; i++)
	{
		//逐行读取学号，姓名，成绩
		infile >> student_list[i].id >> student_list[i].name >> student_list[i].grade;
	}

	//将数组当中的元素按照其成绩高低进行排序
	sort_grade(student_list, student_num);

	for (int i = 0; i < student_num; i++)
	{
		//若某学生分数与前一位学生的相同，则排位与其相同
		if (i != 0 && student_list[i].grade == student_list[i - 1].grade) student_list[i].rank = student_list[i - 1].rank;
		else student_list[i].rank = i + 1;
	}

	//将数组中的元素按照学号排序
	sort_id(student_list, student_num);

	for (int i = 0; i < student_num; i++)
	{
		cout << student_list[i].id << ' ' << student_list[i].name << ' ' << student_list[i].grade << ' '<<student_list[i].rank << endl;
	}

	//释放申请的空间
	delete[] student_list;

	return 0;
}

//该函数用于按照成绩高低排序(选择排序)
void sort_grade(Student student_list[], int num)
{
	Student temp;
	
	for (int i = 0; i < num-1; i++)
	{
		int k = i;
		for (int j = k; j < num; j++)
		{
			if (student_list[j].grade > student_list[k].grade) k = j;
		}

		temp = student_list[i];
		student_list[i] = student_list[k];
		student_list[k] = temp;
	}
}

//该函数用于按照学号排序(选择排序)
void sort_id(Student student_list[], int num)
{
	Student temp;

	for (int i = 0; i < num - 1; i++)
	{
		int k = i;
		for (int j = k; j < num; j++)
		{
			if (student_list[j].id < student_list[k].id) k = j;
		}

		temp = student_list[i];
		student_list[i] = student_list[k];
		student_list[k] = temp;
	}
}



