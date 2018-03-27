/*1751367 计2 彭健聪*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//该函数用于打印当前开关的状态,参数为存储开关状态的short型变量
void switch_stat(short on_off_switch);

int main()
{
	char switch_alpha;//代表开关的字母编号
	char input_stat[4];//接收用户输入ON/OFF指令
	
	//一个short型变量用来存储开关的状态
	short on_off_switch = 0x0000;
	
	cout << "初始状态：" << hex <<"0x"<<setw(4)<<setfill('0')<< on_off_switch << endl;
	switch_stat(on_off_switch);

	//接收用户调整开关状态的指令
	while (1)
	{
		cout << "请以<\"A On /J Off\"形式输出，输入\"Q on/off\"退出>"<<endl;
		cin >> switch_alpha >> input_stat;

		//将用户输入全部转为大写状态
		if (switch_alpha >= 97) switch_alpha -= 32;

		for (int i = 0; i < 4; i++)
		{
			if (input_stat[i] != '\0')
			{
				if (input_stat[i] >= 97) input_stat[i] -= 32;
			}
			else break;
		}

		//判断输入是否合法，否则将重新输入
		if (cin.fail() || switch_alpha<32 ||switch_alpha>74 || (strcmp(input_stat,"OFF")!=0 && strcmp(input_stat,"ON")!=0))
		{
			//判断是否退出
			if (switch_alpha == 'Q') break;
			
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			continue;
		}

		//根据用户指令对变量进行位运算
		if (!strcmp(input_stat, "OFF")) on_off_switch &= 0xFFFF - int(pow(2, switch_alpha - 65));
		else on_off_switch |= 0x0000 + int(pow(2, switch_alpha - 65));

		cout << "当前状态：" << hex << "0x" << setw(4) << setfill('0') << on_off_switch << endl;
		switch_stat(on_off_switch);
	}

	return 0;
}

void switch_stat(short on_off_switch)
{
	cout << "A   B   C   D   E   F   G   H   I   J" << endl;
	
	//逐位检查开关的状态
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