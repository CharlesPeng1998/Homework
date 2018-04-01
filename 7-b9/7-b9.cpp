#include <iostream>
#include <cstdlib> //atoi函数用到
using namespace std;

int main(int argc, char *argv[])
{
	int a, b, t;
	if (argc < 3) /*参数不足3个则出现提示*/
	{
		cerr << "请带两个整数作为参数" << endl;
		return -1;
	}

	for (t = 0; t < argc; t++) /*打印所有的参数值*/
	{
		cout << "argv[" << t << "]=" << argv[t] << endl;
	}
	a = atoi(argv[1]); //atoi是将字符串转为整数的函数
	b = atoi(argv[2]);
	cout << "交换前：a=" << a << " b=" << b << endl;

	t = a;
	a = b;
	b = t;

	cout << "交换后：a=" << a << " b=" << b << endl;
	return 0;
}