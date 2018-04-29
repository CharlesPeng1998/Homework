#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
using namespace std;

//去除字符串头部和尾部的空格
char *alltrim(char *buf)
{
	char *p;
	/*去除尾部空格*/
	p = &buf[strlen(buf) - 1];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p--;
	}
	*(p + 1) = 0;

	/*去除头部空格*/
	p = &buf[0];

	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
	{
		p++;
	}
	/*p移动到buf，含尾零*/
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

	//先把字符串的头尾非有效字符去掉
	strcpy(line, alltrim(line));

	cout << strlen(line) << endl;
	return 0;
}