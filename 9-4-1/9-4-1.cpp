/* 1751367 ��2 ����*/
#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();   //���ѧ�źͳɼ�
					  /* ������Ҫ��������Ա�����Ķ��壬�������� */
	student(int, float);

};

/* �ڴ˸������Ա������ʵ�֣����ⷽʽ�� */
void student::display()
{
	cout << num << ' ' << score << endl;
}

student::student(int n, float s):num(n), score(s)
{}

int main()
{
	student *p, s[5] = { student(1001, 78.5),
		student(1002, 63.5),
		student(1003, 87.5),
		student(1004, 52.5),
		student(1005, 34.5) };
	/* ������� 1001��1003��1005�����˵���Ϣ
	��ע�⣺���������ٶ����κ����͵ı��� */
	s[0].display();
	s[2].display();
	s[4].display();


	return 0;
}
