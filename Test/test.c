/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int *p = (int *)malloc(5*sizeof(int));

	printf("%zd",sizeof(*p));
	
}