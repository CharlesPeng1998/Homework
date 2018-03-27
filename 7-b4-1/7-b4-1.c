/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

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
	struct Student *head;

	FILE *infile;
	infile = fopen("list.txt", "r");
	if (infile == NULL)
	{
		printf("打开文件失败\n");
		return -1;
	}

	//头指针指向表头
	head = (struct Student*)malloc(sizeof(struct Student));
	if (head == NULL)
	{
		printf("No Memory\n");
		return -1;
	}
	//读取第一行的数据
	fscanf(infile, "%d %s %d", &no, name, &score);
	//表头进行二次申请
	head->no = (int*)malloc(sizeof(int));
	if (head->no == NULL)
	{
		printf("No Memory\n");
		return -1;
	}

	head->name = (char*)malloc((strlen(name)+1)*sizeof(char));
	if (head->name == NULL)
	{
		printf("No Memory\n");
		return -1;
	}

	head->score = (int*)malloc(sizeof(int));
	if (head->score == NULL)
	{
		printf("No Memory\n");
		return -1;
	}

	//将第一行数据填入表头
	*head->no = no;
	strcpy(head->name, name);
	*head->score = score;

	struct Student *pointer_1 = head, *pointer_2;

	while (1)
	{
		pointer_2 = (struct Student*)malloc(sizeof(struct Student));
		if (pointer_2 == NULL)
		{
			printf("No Memory\n");
			return -1;
		}

		pointer_1->next = pointer_2;

		fscanf(infile, "%d %s %d", &no, name, &score);

		//进行二次申请
		pointer_2->no = (int*)malloc(sizeof(int));
		if (pointer_2->no == NULL)
		{
			printf("No Memory\n");
			return -1;
		}

		pointer_2->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (pointer_2->name == NULL)
		{
			printf("No Memory\n");
			return -1;
		}

		pointer_2->score = (int*)malloc(sizeof(int));
		if (pointer_2->score == NULL)
		{
			printf("No Memory\n");
			return -1;
		}

		//将数据填入结点
		*pointer_2->no = no;
		strcpy(pointer_2->name, name);
		*pointer_2->score = score;

		if (*pointer_2->no == 9999999)
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
		//打印当前结点信息
		printf("%d %s %d\n", *pointer_1->no, pointer_1->name, *pointer_1->score);
		//指向下一个结点
		pointer_1 = pointer_1->next;
		//释放已打印的结点
		free(pointer_2->no);
		free(pointer_2->name);
		free(pointer_2->score);
		free(pointer_2);

		pointer_2 = pointer_1;

		//判断是否还存在下一个节点
		if (pointer_1 == NULL) break;
	}
	return 0;
}

