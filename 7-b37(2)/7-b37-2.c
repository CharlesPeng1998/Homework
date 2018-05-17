/*1751367 ��2 ����*/
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
	struct Guy *prior;
	struct Guy *next;
}Guy, *Jcircle;

/*******************����ԭ��***********************/
Status InitJcircle(Jcircle *J, int n);
Status DestroyCircle(Jcircle *J);
Guy *Findguy(Jcircle *J, int no);
void JcircleCount(Jcircle *J, int no, int m);
/*******************����ԭ��***********************/

int main()
{
	int n, m, k;
	printf("�������ʼ����n,������ʼ���k,������ֹ��m:");
	scanf("%d %d %d", &n, &k, &m);

	//��Ŵ�������������ȡģ����
	if (k > n)
	{
		k %= n;
	}

	//������ʼԼɪ��
	Jcircle jcircle;
	InitJcircle(&jcircle, n);

	//����������
	JcircleCount(&jcircle, k, m);

	return 0;
}

//��ʼ��Լɪ��
Status InitJcircle(Jcircle *J, int n)
{
	*J = (Guy *)malloc(sizeof(Guy));
	if (*J == NULL)
	{
		exit(LOVERFLOW);
	}

	(*J)->prior = *J;
	(*J)->next = *J;
	

	Guy *p = *J;
	int i;
	for (i = 1; i <= n; i++)
	{
		p->next = (Guy *)malloc(sizeof(Guy));

		if (p->next == NULL)
		{
			exit(LOVERFLOW);
		}

		p->next->no = i;
		p->next->prior = p;
		p = p->next;
	}

	p->next = *J;
	(*J)->prior = p;
	return OK;
}

//Ѱ��ָ����Ž�㲢��������ָ��
Guy *Findguy(Jcircle *J, int no)
{
	Guy *p = *J;

	while (p->no != no)
	{
		p = p->next;
	}

	return p;
}

//��ָ����ŵ��˿�ʼ����
void JcircleCount(Jcircle *J, int no, int m)
{
	//�ҵ�ָ����ŵ���ʼ������
	Guy *curr = Findguy(J, no);

	//��������������������ͷ���ָ������
	while ((*J)->next != *J)
	{
		int i;
		//�ƶ�������m�Ľ�㴦
		for (i = 0; i < m - 1; i++)
		{
			curr = curr->next;

			if (curr == *J)
			{
				curr = curr->next;
			}
		}

		printf("�����˱��:%d\n", curr->no);

		//ɾ�����н��
		curr->prior->next = curr->next;
		curr->next->prior = curr->prior;
		Guy *t = curr;
		curr = curr->next;
		free(t);
	}

	printf("�������Ѿ�����\n");
	//�ͷ�ͷ���
	free(*J);
}