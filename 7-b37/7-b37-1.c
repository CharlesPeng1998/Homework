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
	struct Guy *next;
}Guy,*Jcircle;

/*******************����ԭ��***********************/
Status InitJcircle(Jcircle *J,int n);
Status DestroyCircle(Jcircle *J);
Guy *Findguy(Jcircle *J, int no);
void JcircleCount(Jcircle *J, int no,int m);
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
Status InitJcircle(Jcircle *J,int n)
{
	*J = (Guy *)malloc(sizeof(Guy));
	if (*J == NULL)
	{
		exit(LOVERFLOW);
	}

	Guy *p = *J;

	int i;
	//��������ν������
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

	//���һ���������ָ��ͷ���
	p->next = *J;
	return OK;
}

//�ͷ�Լɪ�򻷣��ƺ�û��Ҫ��
Status DestroyCircle(Jcircle *J)
{
	Jcircle q, p = (*J)->next;

	while (p != *J)
	{
		q = p->next;
		free(p);
		p = q;
	}

	//������ͷ�ͷ���
	free(p);
	return OK;
}

//Ѱ��ָ����Ž�㲢��������ǰ��ָ��
Guy *Findguy(Jcircle *J,int no)
{
	Guy *p = *J;

	while (p->next->no != no)
	{
		p = p->next;
	}
	
	return p;
}

//��ָ����ŵ��˿�ʼ����
void JcircleCount(Jcircle *J, int no,int m)
{
	//�ҵ�ָ����ŵ���ʼ������
	Guy *curr = Findguy(J, no);

	//��������������������ͷ���ָ������
	while ((*J)->next != *J)
	{
		int i;
		//�ƶ�������m�Ľ�㴦
		for (i = 0; i < m-1; i++)
		{
			curr = curr->next;

			if (curr->next == *J)
			{
				curr = curr->next;
			}
		}

		printf("�����˱��:%d\n", curr->next->no);

		//ɾ�����н��
		Guy *t = curr->next;
		curr->next = curr->next->next;
		free(t);
	}

	printf("�������Ѿ�����\n");
	//�ͷ�ͷ���
	free(*J);
}



