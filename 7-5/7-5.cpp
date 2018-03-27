/*1751367 计2 彭健聪*/
#include <iostream>
#include <iomanip>
#define NUM 10
using namespace std;

struct Student
{
	int no;
	char name[9];
	float score[3];
	float avg_score;
	float total_score;
};

//接收用户输入
void input_info(struct Student info[]);
//打印学生信息
void print_info(struct Student info[]);
//打印高分学生信息
void print_top(struct Student info[]);

int main()
{
	Student student_info[NUM];
	
	input_info(student_info);
	print_info(student_info);
	print_top(student_info);
	return 0;
}

void input_info(Student info[])
{
	for (int i = 0; i < NUM; i++)
	{
		cout << "请输入第";
		cout << setiosflags(ios::right) << setw(2)<< i+1;
		cout << "个学生的信息：";
		cin >> info[i].no >> info[i].name >> info[i].score[0] >> info[i].score[1] >> info[i].score[2];
		cout << resetiosflags(ios::right);
	}

	cout << endl;
}

void print_info(Student info[])
{
	cout << "10个学生的成绩为：" << endl;
	cout << "序号 学号    姓名     三门课成绩    平均成绩" << endl;
	cout << "============================================" << endl;

	cout << setiosflags(ios::left);
	for (int i = 0; i < NUM; i++)
	{
		
		
		cout << setw(4)<< i + 1<<' ';
		cout << setw(4)<< info[i].no<<' ';
		cout << setw(8)<< info[i].name<<' ';
		
		for (int j = 0; j < 3; j++)
		{
			cout << setw(4)<<info[i].score[j]<<' ';
		}

		info[i].avg_score = (info[i].score[0] + info[i].score[1] + info[i].score[2]) / 3;

		cout <<setw(5)<<setiosflags(ios::fixed)<<setprecision(2)<< info[i].avg_score<< endl;
		cout << resetiosflags(ios::fixed) << setprecision(6);
	}

	cout << endl;
}

void print_top(struct Student info[])
{
	int i;
	for (i = 0; i < NUM; i++)
	{
		info[i].total_score = info[i].score[0] + info[i].score[1] + info[i].score[2];
	}
	//寻找总分最大值
	float max_score = info[0].total_score;
	for (i = 1; i < NUM; i++)
	{
		if (info[i].total_score > max_score) max_score = info[i].total_score;
	}

	cout << "最高分学生信息：" << endl;
	cout << "序号 学号    姓名     三门课成绩     总成绩" << endl;
	cout << "===========================================" << endl;

	for (int i = 0; i < NUM; i++)
	{
		if (info[i].total_score == max_score)
		{
			cout << setw(4) << i + 1 << ' ';
			cout << setw(4) << info[i].no << ' ';
			cout << setw(8) << info[i].name << ' ';

			for (int j = 0; j < 3; j++)
			{
				cout << setw(4) << info[i].score[j]<<' ';
			}

			cout << setw(5) << setiosflags(ios::fixed) << setprecision(1) << info[i].total_score << endl;
			cout << resetiosflags(ios::fixed) << setprecision(6);
		}
	}
}