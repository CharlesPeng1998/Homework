/*1751367 ��2 ����*/
#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();  //���ѧ�źͳɼ�
	void get(void);  //��������ѧ�źͳɼ�
					 //���в�����������κ����ݳ�Ա�ͳ�Ա����
};

/* �ڴ˸������Ա����������ʵ�� */
void student::display()
{
	cout << "ѧ��:" << num << ' ' << "�ɼ�:" << score << endl;
}

void student::get(void)
{
	cin >> num >> score;
}

int main()
{
	/* ��ע�⣺�������в������ٶ����κ����͵ı���(����ȫ�ֱ���) */
	student *p, s[5];

	/* ��������5���˵�ѧ�ż��ɼ�
	��Ҫ�󣺡����������ȷ��������ʾ�����硰�������**����ѧ�źͳɼ��� */
	for (int i = 0; i < 5; i++)
	{
		cout << "�������" << i + 1 << "����ѧ�źͳɼ�:";
		s[i].get();
	}


	/* �����1��3��5���˵���Ϣ */
	s[0].display();
	s[2].display();
	s[4].display();

	return 0;
}