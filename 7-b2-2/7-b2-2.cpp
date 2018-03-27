/*1751367 ��2 ����*/
#include <iostream>
#include <fstream>
using namespace std;

//����һ��ѧ���ṹ��
struct Student
{
	int id;
	char name[7];
	int grade;
	int rank;
};

void bubble_sort_grade(Student[], int);
void sort_id(Student[], int);


int main()
{
	int student_num;//ѧ��������
	Student *student_list = new(nothrow) Student[80];

	//�����붯̬�ռ�ʧ���򱨴��˳�
	if (student_list == NULL)
	{
		cout << "No Memory";
		return -1;
	}

	ifstream infile;
	infile.open("student.txt", ios::in);//���ļ�
	if (infile.is_open() == 0)
	{
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}

	infile >> student_num;//��ȡ�ļ���һ�е�ѧ��������

	for (int i = 0; i < student_num; i++)
	{
		//���ж�ȡѧ�ţ��������ɼ�
		infile >> student_list[i].id >> student_list[i].name >> student_list[i].grade;
	}

	sort_id(student_list, student_num);
	bubble_sort_grade(student_list, student_num);

	for (int i = 0; i < student_num; i++)
	{
		//��ĳѧ��������ǰһλѧ������ͬ������λ������ͬ
		if (i != 0 && student_list[i].grade == student_list[i - 1].grade) student_list[i].rank = student_list[i - 1].rank;
		else student_list[i].rank = i + 1;
	}

	for (int i = 0; i < student_num; i++)
	{
		cout << student_list[i].id << ' ' << student_list[i].name << ' ' << student_list[i].grade << ' ' << student_list[i].rank << endl;
	}

	//�ͷ�����Ŀռ�
	delete[] student_list;

	return 0;
}

//�ú������ڰ���ѧ������(ѡ������)
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

//�ú������ڰ��ɼ�����ð������
void bubble_sort_grade(Student student_list[], int num)
{
	Student temp;
	
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i-1; j++)
		{
			if (student_list[j].grade < student_list[j + 1].grade)
			{
				temp = student_list[j];
				student_list[j] = student_list[j+1];
				student_list[j+1] = temp;
			}
		}
	}
}