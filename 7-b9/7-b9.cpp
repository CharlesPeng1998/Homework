#include <iostream>
#include <cstdlib> //atoi�����õ�
using namespace std;

int main(int argc, char *argv[])
{
	int a, b, t;
	if (argc < 3) /*��������3���������ʾ*/
	{
		cerr << "�������������Ϊ����" << endl;
		return -1;
	}

	for (t = 0; t < argc; t++) /*��ӡ���еĲ���ֵ*/
	{
		cout << "argv[" << t << "]=" << argv[t] << endl;
	}
	a = atoi(argv[1]); //atoi�ǽ��ַ���תΪ�����ĺ���
	b = atoi(argv[2]);
	cout << "����ǰ��a=" << a << " b=" << b << endl;

	t = a;
	a = b;
	b = t;

	cout << "������a=" << a << " b=" << b << endl;
	return 0;
}