/*1751367 ��2 ����*/
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

/*******************����ԭ��***********************/
Status InitPolynomial(polynomial *P);
Status DestroyList(polynomial *P);
polynode *GetPosPtr(polynomial P, int expn);
Status PolynodeInsert(polynomial *P, double coef, int expn);
void PrintPolynomial(polynomial P);
void PolynomialAdd(polynomial *p1, polynomial *p2);
void PolynomialSubtract(polynomial *p1, polynomial *p2);
/*******************����ԭ��***********************/

int main()
{
	int choice;
	printf("1.����ʽ�Ľ���\n2.����ʽ�����\n3.����ʽ�����\n");
	printf("��ѡ��[1-3]:");
	scanf("%d", &choice);

	//����ʽ�Ľ���
	if (choice == 1)
	{
		//����ʽ����ĳ�ʼ��
		polynomial plnm;
		InitPolynomial(&plnm);

		double coef;
		int expn;
		printf("����������ϵ����ָ��(ָ��-1�����������):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm, coef, expn))
			{
				printf("����ʽ����ʧ��\n");
				return -1;
			}
		}

		printf("����ʽ�����ɹ�:\n");
		PrintPolynomial(plnm);

		DestroyList(&plnm);
	}

	//����ʽ�����
	else if (choice == 2)
	{
		//��ʼ����������ʽ
		polynomial plnm1, plnm2;
		InitPolynomial(&plnm1);
		InitPolynomial(&plnm2);

		double coef;
		int expn;
		
		//������һ������ʽ
		printf("�������һ������ʽ�����ϵ����ָ��(ָ��-1�����������):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm1, coef, expn))
			{
				printf("����ʽ����ʧ��\n");
				return -1;
			}
		}

		//�����ڶ�������ʽ
		printf("\n������ڶ�������ʽ�����ϵ����ָ��(ָ��-1�����������):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm2, coef, expn))
			{
				printf("����ʽ����ʧ��\n");
				return -1;
			}
		}

		printf("\n��1������ʽ:\n");
		PrintPolynomial(plnm1);

		printf("\n��2������ʽ:\n");
		PrintPolynomial(plnm2);

		//���ж���ʽ���
		PolynomialAdd(&plnm1, &plnm2);
		printf("\n����ʽ��ӽ��:\n");
		PrintPolynomial(plnm1);

		DestroyList(&plnm1);
	}

	//����ʽ�����
	else if (choice == 3)
	{
		//��ʼ����������ʽ
		polynomial plnm1, plnm2;
		InitPolynomial(&plnm1);
		InitPolynomial(&plnm2);

		double coef;
		int expn;

		//������һ������ʽ
		printf("�������һ������ʽ�����ϵ����ָ��(ָ��-1�����������):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm1, coef, expn))
			{
				printf("����ʽ����ʧ��\n");
				return -1;
			}
		}

		//�����ڶ�������ʽ
		printf("\n������ڶ�������ʽ�����ϵ����ָ��(ָ��-1�����������):\n");

		while (scanf("%lf %d", &coef, &expn) && expn != -1)
		{
			if (!PolynodeInsert(&plnm2, coef, expn))
			{
				printf("����ʽ����ʧ��\n");
				return -1;
			}
		}

		printf("\n��1������ʽ:\n");
		PrintPolynomial(plnm1);

		printf("\n��2������ʽ:\n");
		PrintPolynomial(plnm2);

		//���ж���ʽ���
		PolynomialSubtract(&plnm1, &plnm2);
		printf("\n����ʽ������:\n");
		PrintPolynomial(plnm1);

		DestroyList(&plnm1);
	}
	else
	{
		printf("ѡ�����!\n");
	}

	return 0;
}

//��ʼ������ʽ����
Status InitPolynomial(polynomial *P)
{
	*P = (polynode *)malloc(sizeof(polynode));
	if (*P == NULL)
		exit(LOVERFLOW);

	(*P)->next = NULL;
	return OK;
}

//ɾ������ʽ����
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

//��������ָ��Ѱ�Һ��ʲ���λ�õ�ǰ��ָ��
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

//����Ĳ���
Status PolynodeInsert(polynomial *P, double coef, int expn)
{
	if (coef == 0)
	{
		return OK;
	}

	polynode *p = GetPosPtr(*P, expn);

	//���Ѵ�����ָͬ���������ʱֻ��Ҫ��ԭ���ϵ�������
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

//��ӡ����ʽ
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

//����ʽ�����
void PolynomialAdd(polynomial *p1, polynomial *p2)
{
	//���ڶ�������ʽ�鲢����һ������ʽ
	
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

//����ʽ�����
void PolynomialSubtract(polynomial *p1, polynomial *p2)
{
	//���ڶ�������ʽ�鲢����һ������ʽ

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



