#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
using namespace std;

//ȥ���ַ���ͷ����β���Ŀո�
char *alltrim(char *buf)
{
	char *p;
	/*ȥ��β���ո�*/
	p = &buf[strlen(buf) - 1];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p--;
	}
	*(p + 1) = 0;

	/*ȥ��ͷ���ո�*/
	p = &buf[0];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p++;
	}
	/*p�ƶ���buf����β��*/
	if (p != buf)
	{
		memmove(buf, p, strlen(p) + 1);
	}

	return buf;
}

int main()
{
	fstream infile("test.txt", ios::in);

	char line[10] = { 0 };

	//�Ȱ��ַ�����ͷβ����Ч�ַ�ȥ��
	strcpy(line, alltrim(line));

	cout << strlen(line) << endl;
	return 0;
}