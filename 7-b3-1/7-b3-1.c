/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>

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
	struct Student *head;

	FILE *infile;
	infile = fopen("list.txt", "r");
	if (infile == NULL)
	{
		printf("���ļ�ʧ��\n");
		return -1;
	}

	//ͷָ��ָ���ͷ
	head = (struct Student*)malloc(sizeof(struct Student));
	if (head == NULL)
	{
		printf("No Memory\n");
		return -1;
	}
	fscanf(infile, "%d %s %d", &head->no, head->name, &head->score);

	struct Student *pointer_1 = head, *pointer_2;

	while (1)
	{
		pointer_2= (struct Student*)malloc(sizeof(struct Student));

		if (pointer_2 == NULL)
		{
			printf("No Memory\n");
			return -1;
		}

		pointer_1->next = pointer_2;

		fscanf(infile,"%d %s %d", &pointer_2->no, pointer_2->name, &pointer_2->score);

		if (pointer_2->no == 9999999)
		{
			free(pointer_2);
			pointer_1->next = NULL;
			break;
		}
		else pointer_1 = pointer_2;
	}

	pointer_2 = pointer_1 = head;

	while (1)
	{
		//��ӡ��ǰ�����Ϣ
		printf("%d %s %d\n", pointer_1->no, pointer_1->name, pointer_1->score);
		//ָ����һ�����
		pointer_1 = pointer_1->next;
		//�ͷ��Ѵ�ӡ�Ľ��
		free(pointer_2);

		pointer_2 = pointer_1;

		//�ж��Ƿ񻹴�����һ���ڵ�
		if (pointer_1 == NULL) break;
	}

	return 0;
}
