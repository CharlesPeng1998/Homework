/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#define NUM 10
#include "stdio.h"

struct Student
{
	int no;
	char name[9];
	float score[3];
	float avg_score;
	float total_score;
};

//�����û�����
void input_info(struct Student info[]);
//��ӡѧ����Ϣ
void print_info(struct Student info[]);
//��ӡ�߷�ѧ����Ϣ
void print_top(struct Student info[]);

int main()
{
	struct Student student_info[NUM];

	input_info(student_info);
	print_info(student_info);
	print_top(student_info);
	return 0;
}

void input_info(struct Student info[])
{
	int i;
	for (i = 0; i < NUM; i++)
	{
		printf("�������%2d��ѧ������Ϣ��", i + 1);
		scanf("%d %s %f %f %f", &info[i].no, info[i].name, &info[i].score[0], &info[i].score[1], &info[i].score[2]);
	}
	printf("\n");
}

void print_info(struct Student info[])
{
	printf("10��ѧ���ĳɼ�Ϊ��\n");
	printf("��� ѧ��    ����     ���ųɼ�       ƽ���ɼ�\n");
	printf("=============================================\n");
	
	int i;
	for (i = 0; i < NUM; i++)
	{
		info[i].avg_score = (info[i].score[0] + info[i].score[1] + info[i].score[2]) / 3;
		printf("%-4d %-4d %-8s %-4g %-4g %-4g %-5.2f\n", i + 1, info[i].no, info[i].name, info[i].score[0], info[i].score[1], info[i].score[2], info[i].avg_score);
	}

	printf("\n");
}

void print_top(struct Student info[])
{
	int i;
	for (i = 0; i < NUM; i++)
	{
		info[i].total_score = info[i].score[0] + info[i].score[1] + info[i].score[2];
	}
	//Ѱ���ܷ����ֵ
	float max_score = info[0].total_score;
	for (i = 1; i < NUM; i++)
	{
		if (info[i].total_score > max_score) max_score = info[i].total_score;
	}

	printf("10��ѧ���ĳɼ�Ϊ��\n");
	printf("��� ѧ��    ����     ���ųɼ�       �ܳɼ�\n");
	printf("===========================================\n");

	for (i = 0; i < NUM; i++)
	{
		if (info[i].total_score == max_score)
		{
			printf("%-4d %-4d %-8s %-4g %-4g %-4g %-4g\n", i + 1, info[i].no, info[i].name, info[i].score[0], info[i].score[1], info[i].score[2], info[i].total_score);
		}
	}
}



