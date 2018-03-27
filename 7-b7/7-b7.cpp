/*1751367 ��2 ����*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//�ú������ڴ�ӡ��ǰ���ص�״̬,����Ϊ�洢����״̬��short�ͱ���
void switch_stat(short on_off_switch);

int main()
{
	char switch_alpha;//�����ص���ĸ���
	char input_stat[4];//�����û�����ON/OFFָ��
	
	//һ��short�ͱ��������洢���ص�״̬
	short on_off_switch = 0x0000;
	
	cout << "��ʼ״̬��" << hex <<"0x"<<setw(4)<<setfill('0')<< on_off_switch << endl;
	switch_stat(on_off_switch);

	//�����û���������״̬��ָ��
	while (1)
	{
		cout << "����<\"A On /J Off\"��ʽ���������\"Q on/off\"�˳�>"<<endl;
		cin >> switch_alpha >> input_stat;

		//���û�����ȫ��תΪ��д״̬
		if (switch_alpha >= 97) switch_alpha -= 32;

		for (int i = 0; i < 4; i++)
		{
			if (input_stat[i] != '\0')
			{
				if (input_stat[i] >= 97) input_stat[i] -= 32;
			}
			else break;
		}

		//�ж������Ƿ�Ϸ���������������
		if (cin.fail() || switch_alpha<32 ||switch_alpha>74 || (strcmp(input_stat,"OFF")!=0 && strcmp(input_stat,"ON")!=0))
		{
			//�ж��Ƿ��˳�
			if (switch_alpha == 'Q') break;
			
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			continue;
		}

		//�����û�ָ��Ա�������λ����
		if (!strcmp(input_stat, "OFF")) on_off_switch &= 0xFFFF - int(pow(2, switch_alpha - 65));
		else on_off_switch |= 0x0000 + int(pow(2, switch_alpha - 65));

		cout << "��ǰ״̬��" << hex << "0x" << setw(4) << setfill('0') << on_off_switch << endl;
		switch_stat(on_off_switch);
	}

	return 0;
}

void switch_stat(short on_off_switch)
{
	cout << "A   B   C   D   E   F   G   H   I   J" << endl;
	
	//��λ��鿪�ص�״̬
	for (int i = 0; i < 10; i++)
	{
		if (on_off_switch & int(pow(2, i)))
		{
			cout << "ON " << ' ';
		}
		else cout << "OFF" << ' ';
	}
	cout << endl << endl;
}