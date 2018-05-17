/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LOVERFLOW -2

typedef int Status;

typedef struct Guy
{
	int no;
	struct Guy *next;
}Guy,*Jcircle;

/*******************函数原型***********************/
Status InitJcircle(Jcircle *J,int n);
Status DestroyCircle(Jcircle *J);
Guy *Findguy(Jcircle *J, int no);
void JcircleCount(Jcircle *J, int no,int m);
/*******************函数原型***********************/

int main()
{
	int n, m, k;
	printf("请输入初始人数n,报数起始编号k,报数终止数m:");
	scanf("%d %d %d", &n, &k, &m);

	//编号大于总人数，做取模操作
	if (k > n)
	{
		k %= n;
	}

	//建立初始约瑟夫环
	Jcircle jcircle;
	InitJcircle(&jcircle, n);

	//报数并出列
	JcircleCount(&jcircle, k, m);

	return 0;
}

//初始化约瑟夫环
Status InitJcircle(Jcircle *J,int n)
{
	*J = (Guy *)malloc(sizeof(Guy));
	if (*J == NULL)
	{
		exit(LOVERFLOW);
	}

	Guy *p = *J;

	int i;
	//按编号依次建立结点
	for (i = 1; i <= n; i++)
	{
		p->next = (Guy *)malloc(sizeof(Guy));

		if (p->next == NULL)
		{
			exit(LOVERFLOW);
		}

		p->next->no = i;
		p = p->next;
	}

	//最后一个结点重新指向头结点
	p->next = *J;
	return OK;
}

//释放约瑟夫环（似乎没必要）
Status DestroyCircle(Jcircle *J)
{
	Jcircle q, p = (*J)->next;

	while (p != *J)
	{
		q = p->next;
		free(p);
		p = q;
	}

	//最后再释放头结点
	free(p);
	return OK;
}

//寻找指定编号结点并返回它的前驱指针
Guy *Findguy(Jcircle *J,int no)
{
	Guy *p = *J;

	while (p->next->no != no)
	{
		p = p->next;
	}
	
	return p;
}

//从指定编号的人开始报数
void JcircleCount(Jcircle *J, int no,int m)
{
	//找到指定编号的起始报数人
	Guy *curr = Findguy(J, no);

	//报数结束的条件：链表头结点指向自身
	while ((*J)->next != *J)
	{
		int i;
		//移动到报数m的结点处
		for (i = 0; i < m-1; i++)
		{
			curr = curr->next;

			if (curr->next == *J)
			{
				curr = curr->next;
			}
		}

		printf("出列人编号:%d\n", curr->next->no);

		//删除出列结点
		Guy *t = curr->next;
		curr->next = curr->next->next;
		free(t);
	}

	printf("所有人已经出列\n");
	//释放头结点
	free(*J);
}



