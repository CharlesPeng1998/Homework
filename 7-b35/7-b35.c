/*1751367 计2 彭健聪*/
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

/*******************函数原型***********************/
Status InitList(DuLinkList *L);
Status DestroyList(DuLinkList *L);
int ListLength(DuLinkList L);
DuLNode *GetElemP_DuL(DuLinkList L, int i);
Status ListInsert_DuL(DuLinkList *L, int i, Student student);
Status ListDelete_DuL(DuLinkList *L, int i);
void PrintList(DuLinkList L);
/*******************函数原型***********************/

int main()
{
	int i;
	int pos;
	DuLinkList list;

	//初始化链表
	InitList(&list);

	//初始化插入6个元素
	Student students[6] =
	{
		{ 1001,"张三",'M',76.5,"上海市杨浦区" },
	{ 1002,"李四",'F',87,"上海市普陀区" },
	{ 1003,"王五",'M',80,"浙江省杭州市" },
	{ 1004,"赵六",'M',54,"浙江省绍兴市" },
	{ 1005,"牛七",'F',85,"江苏省南京市" },
	{ 1006,"马八",'M',60,"江苏省苏州市" }
	};

	//插入初始元素
	for (i = 0; i < 6; i++)
	{
		ListInsert_DuL(&list, i + 1, students[i]);
	}

	//打印初始元素
	printf("初始化插入6个元素:\n");
	PrintList(list);

	for (i = 0; i < 3; i++)
	{
		printf("请输入要删除元素的位序[1..%d]:",ListLength(list));
		scanf("%d", &pos);

		if (ListDelete_DuL(&list, pos))
		{
			printf("删除第%d元素成功\n新表为:", pos);
			PrintList(list);
			printf("\n第%d次演示结束\n", i + 1);
		}
	}

	//删除双向循环链表
	DestroyList(&list);
	return 0;
}

//初始化线性表
Status InitList(DuLinkList *L)
{
	//申请头结点空间，赋值给头指针
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	if (*L == NULL)
	{
		exit(LOVERFLOW);
	}

	//只有一个头结点的双向循环链表，prior和next均指向自身
	(*L)->prior = *L;
	(*L)->next = *L;
	return OK;
}

//删除双向循环链表
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

	//最后再释放头结点
	free(p->data);
	free(p);
	return OK;
}

//求双向循环链表的长度
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next; //指向首元结点
	int len = 0;

	while (p != L)
	{
		p = p->next;
		len++;
	}
	return len;
}

//取指向指定位置结点的指针
DuLNode *GetElemP_DuL(DuLinkList L, int i)
{
	//返回第i个结点的指针
	//i=length+1时，返回头指针
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

//在指定位置插入新的结点
Status ListInsert_DuL(DuLinkList *L, int i, Student student)
{
	//判断i是否合法
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

//打印链表元素
void PrintList(DuLinkList L)
{
	DuLinkList p = L->next;

	while (p != L)
	{
		printf("%d-%s-%c-%f-%s->\n", p->data->num, p->data->name, p->data->sex, p->data->score, p->data->addr);
		p = p->next;
	}
}

//删除指定结点
Status ListDelete_DuL(DuLinkList *L, int i)
{
	//判断i是否合法
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