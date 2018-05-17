/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LOVERFLOW -2

typedef int Status;

typedef struct Student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} Student;

typedef struct DuLNode
{
	Student *data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;

/*******************����ԭ��***********************/
Status InitList(DuLinkList *L);
Status DestroyList(DuLinkList *L);
int ListLength(DuLinkList L);
DuLNode *GetElemP_DuL(DuLinkList L, int i);
Status ListInsert_DuL(DuLinkList *L, int i, Student student);
Status ListDelete_DuL(DuLinkList *L, int i);
void PrintList(DuLinkList L);
/*******************����ԭ��***********************/

int main()
{
	int i;
	int pos;
	DuLinkList list;

	//��ʼ������
	InitList(&list);

	//��ʼ������6��Ԫ��
	Student students[6] =
	{
		{ 1001,"����",'M',76.5,"�Ϻ���������" },
	{ 1002,"����",'F',87,"�Ϻ���������" },
	{ 1003,"����",'M',80,"�㽭ʡ������" },
	{ 1004,"����",'M',54,"�㽭ʡ������" },
	{ 1005,"ţ��",'F',85,"����ʡ�Ͼ���" },
	{ 1006,"���",'M',60,"����ʡ������" }
	};

	//�����ʼԪ��
	for (i = 0; i < 6; i++)
	{
		ListInsert_DuL(&list, i + 1, students[i]);
	}

	//��ӡ��ʼԪ��
	printf("��ʼ������6��Ԫ��:\n");
	PrintList(list);

	for (i = 0; i < 3; i++)
	{
		printf("������Ҫɾ��Ԫ�ص�λ��[1..%d]:",ListLength(list));
		scanf("%d", &pos);

		if (ListDelete_DuL(&list, pos))
		{
			printf("ɾ����%dԪ�سɹ�\n�±�Ϊ:", pos);
			PrintList(list);
			printf("\n��%d����ʾ����\n", i + 1);
		}
	}

	//ɾ��˫��ѭ������
	DestroyList(&list);
	return 0;
}

//��ʼ�����Ա�
Status InitList(DuLinkList *L)
{
	//����ͷ���ռ䣬��ֵ��ͷָ��
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	if (*L == NULL)
	{
		exit(LOVERFLOW);
	}

	//ֻ��һ��ͷ����˫��ѭ������prior��next��ָ������
	(*L)->prior = *L;
	(*L)->next = *L;
	return OK;
}

//ɾ��˫��ѭ������
Status DestroyList(DuLinkList *L)
{
	DuLinkList q, p = (*L)->next;

	while (p != *L)
	{
		q = p->next;
		free(p->data);
		free(p);
		p = q;
	}

	//������ͷ�ͷ���
	free(p->data);
	free(p);
	return OK;
}

//��˫��ѭ������ĳ���
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	while (p != L)
	{
		p = p->next;
		len++;
	}
	return len;
}

//ȡָ��ָ��λ�ý���ָ��
DuLNode *GetElemP_DuL(DuLinkList L, int i)
{
	//���ص�i������ָ��
	//i=length+1ʱ������ͷָ��
	int len = ListLength(L);

	if (i == len + 1)
	{
		return L;
	}

	DuLinkList p = L->next;
	int pos = 1;
	while (p != L && pos < i)
	{
		p = p->next;
		pos++;
	}
	return p;
}

//��ָ��λ�ò����µĽ��
Status ListInsert_DuL(DuLinkList *L, int i, Student student)
{
	//�ж�i�Ƿ�Ϸ�
	if (i<1 || i>ListLength(*L) + 1)
	{
		return ERROR;
	}

	DuLNode *p = GetElemP_DuL(*L, i);

	DuLNode *s;
	if (!(s = (DuLNode *)malloc(sizeof(DuLNode))))
	{
		return ERROR;
	}

	s->data = (Student *)malloc(sizeof(Student));
	memcpy(s->data, &student, sizeof(Student));
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

//��ӡ����Ԫ��
void PrintList(DuLinkList L)
{
	DuLinkList p = L->next;

	while (p != L)
	{
		printf("%d-%s-%c-%f-%s->\n", p->data->num, p->data->name, p->data->sex, p->data->score, p->data->addr);
		p = p->next;
	}
}

//ɾ��ָ�����
Status ListDelete_DuL(DuLinkList *L, int i)
{
	//�ж�i�Ƿ�Ϸ�
	if (i<1 || i>ListLength(*L))
	{
		return ERROR;
	}

	DuLNode *p = GetElemP_DuL(*L, i);
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p->data);
	free(p);

	return OK;
}