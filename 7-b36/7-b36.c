/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LOVERFLOW -2

typedef int Status;

typedef struct polynode
{
	double coef;
	int expn;
	struct polynode *next;
}polynode, *polynomial;

/*******************函数原型***********************/
Status InitPolynomial(polynomial *P);
Status DestroyList(polynomial *P);
polynode *GetPosPtr(polynomial P, int expn);
Status PolynodeInsert(polynomial *P, double coef, int expn);
void PrintPolynomial(polynomial P);
void PolynomialAdd(polynomial *p1, polynomial *p2);
void PolynomialSubtract(polynomial *p1, polynomial *p2);
/*******************函数原型***********************/

int main()
{
	int choice;
	printf("1.多项式的建立\n2.多项式的相加\n3.多项式的相减\n");
	printf("请选择[1-3]:");
	scanf("%d", &choice);

	//多项式的建立
	if (choice == 1)
	{
		//多项式链表的初始化
		polynomial plnm;
		InitPolynomial(&plnm);

		double coef;
		int expn;
		printf("请输入各项的系数和指数(指数-1代表输入结束):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm, coef, expn))
			{
				printf("多项式生成失败\n");
				return -1;
			}
		}

		printf("多项式建立成功:\n");
		PrintPolynomial(plnm);

		DestroyList(&plnm);
	}

	//多项式的相加
	else if (choice == 2)
	{
		//初始化两个多项式
		polynomial plnm1, plnm2;
		InitPolynomial(&plnm1);
		InitPolynomial(&plnm2);

		double coef;
		int expn;
		
		//建立第一个多项式
		printf("请输入第一个多项式各项的系数和指数(指数-1代表输入结束):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm1, coef, expn))
			{
				printf("多项式生成失败\n");
				return -1;
			}
		}

		//建立第二个多项式
		printf("\n请输入第二个多项式各项的系数和指数(指数-1代表输入结束):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm2, coef, expn))
			{
				printf("多项式生成失败\n");
				return -1;
			}
		}

		printf("\n第1个多项式:\n");
		PrintPolynomial(plnm1);

		printf("\n第2个多项式:\n");
		PrintPolynomial(plnm2);

		//进行多项式相加
		PolynomialAdd(&plnm1, &plnm2);
		printf("\n多项式相加结果:\n");
		PrintPolynomial(plnm1);

		DestroyList(&plnm1);
	}

	//多项式的相减
	else if (choice == 3)
	{
		//初始化两个多项式
		polynomial plnm1, plnm2;
		InitPolynomial(&plnm1);
		InitPolynomial(&plnm2);

		double coef;
		int expn;

		//建立第一个多项式
		printf("请输入第一个多项式各项的系数和指数(指数-1代表输入结束):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm1, coef, expn))
			{
				printf("多项式生成失败\n");
				return -1;
			}
		}

		//建立第二个多项式
		printf("\n请输入第二个多项式各项的系数和指数(指数-1代表输入结束):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm2, coef, expn))
			{
				printf("多项式生成失败\n");
				return -1;
			}
		}

		printf("\n第1个多项式:\n");
		PrintPolynomial(plnm1);

		printf("\n第2个多项式:\n");
		PrintPolynomial(plnm2);

		//进行多项式相减
		PolynomialSubtract(&plnm1, &plnm2);
		printf("\n多项式相减结果:\n");
		PrintPolynomial(plnm1);

		DestroyList(&plnm1);
	}
	else
	{
		printf("选择错误!\n");
	}

	return 0;
}

//初始化多项式链表
Status InitPolynomial(polynomial *P)
{
	*P = (polynode *)malloc(sizeof(polynode));
	if (*P == NULL)
		exit(LOVERFLOW);

	(*P)->next = NULL;
	return OK;
}

//删除多项式链表
Status DestroyList(polynomial *P)
{
	polynomial q, p = *P;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	*P = NULL;
	return OK;
}

//根据所给指数寻找合适插入位置的前驱指针
polynode *GetPosPtr(polynomial P, int expn)
{
	polynomial p = P;
	
	while (p->next != NULL)
	{
		if (p->next->expn <= expn)
		{
			p = p->next;
		}
		else break;
	}

	return p;
}

//项结点的插入
Status PolynodeInsert(polynomial *P, double coef, int expn)
{
	if (coef == 0)
	{
		return OK;
	}

	polynode *p = GetPosPtr(*P, expn);

	//若已存在相同指数的项，插入时只需要在原项的系数上添加
	if (expn == p->expn)
	{
		p->expn += expn;
	}
	else
	{
		polynode *s;
		if (!(s = (polynode *)malloc(sizeof(polynode))))
		{
			return ERROR;
		}

		s->coef = coef;
		s->expn = expn;

		polynode *u = p->next;
		p->next = s;
		s->next = u;
	}

	return OK;
}

//打印多项式
void PrintPolynomial(polynomial P)
{
	polynode *p = P->next;
	
	printf("P(x)=");
	while (p != NULL)
	{
		if (p->next != NULL)
		{
			printf("%lfx^%d+", p->coef, p->expn);
		}
		else printf("%lfx^%d\n", p->coef, p->expn);

		p = p->next;
	}
}

//多项式的相加
void PolynomialAdd(polynomial *p1, polynomial *p2)
{
	//将第二个多项式归并到第一个多项式
	
	polynode *pre = *p1;
	polynode *p = (*p1)->next;
	polynode *q = (*p2)->next;

	while (p != NULL && q!=NULL)
	{
		if (p->expn < q->expn)
		{
			pre = p;
			p = p->next;
		}
		else if (p->expn == q->expn)
		{
			double x = p->coef + q->coef;

			if (fabs(x) > 1e-6)
			{
				p->coef = x;
				pre = p;
			}
			else
			{
				pre->next = p->next;
				free(p);
			}

			p = pre->next;
			polynode *u = q;
			q = q->next;
			free(u);
		}
		else if (p->expn > q->expn)
		{
			polynode *u = q->next;
			q->next = p;
			pre->next = q;
			pre = q;
			q = u;
		}
	}
}

//多项式的相减
void PolynomialSubtract(polynomial *p1, polynomial *p2)
{
	//将第二个多项式归并到第一个多项式

	polynode *pre = *p1;
	polynode *p = (*p1)->next;
	polynode *q = (*p2)->next;

	while (p != NULL && q != NULL)
	{
		if (p->expn < q->expn)
		{
			pre = p;
			p = p->next;
		}
		else if (p->expn == q->expn)
		{
			double x = p->coef - q->coef;

			if (fabs(x) > 1e-6)
			{
				p->coef = x;
				pre = p;
			}
			else
			{
				pre->next = p->next;
				free(p);
			}

			p = pre->next;
			polynode *u = q;
			q = q->next;
			free(u);
		}
		else if (p->expn > q->expn)
		{
			q->coef *= -1;

			polynode *u = q->next;
			q->next = p;
			pre->next = q;
			pre = q;
			q = u;
		}
	}
}



