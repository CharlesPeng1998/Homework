/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <cstdlib>

#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

#elif defined(_MSC_VER)
#include <Windows.h>

#endif



#define ITEMS_NUM 25
#define DATA_NUM 64

//各属性值在文件当中的位置
#define HP 17
#define STRENGTH 19
#define CONSTITUTION 21
#define DEXTERITY 23
#define GOLD 25
#define FAME 29
#define CHARM 33
#define MOVING_SPEED 45
#define ATTACK_SPEED 46
#define ATTACK_RANGE 47
#define ATTACK_POWER 49
#define DEFENSE_FORCE 51
#define AGILITY 53
#define IQ 54
#define EXP 55
#define LEVEL 56
#define MP 57
#define COST_MANA 59
#define MAGIC_DAMAGE 60
#define HIT_RATE 61
#define MAGIC_DEFENSE 62
#define CRIT_RATE 63
#define ENDURANCE 64

using namespace std;

const char *menu_items[ITEMS_NUM] = { "1.修改玩家昵称（最多15个字符）",
"2.修改生命值（0-10000）",
"3.修改力量值（0-10000）",
"4.修改体质（0-8192）",
"5.修改灵巧（0-1024）",
"6.修改金钱数量（0-100000000）",
"7.修改名声值（0-1000000）",
"8.修改魅力值（0-1000000）",
"9.修改移动速度（0-100）",
"10.修改攻击速度（0-100）",
"11.修改攻击范围（0-100）",
"12.修改攻击力（0-2000）",
"13.修改防御力（0-2000）",
"14.修改敏捷度（0-100）",
"15.修改智力（0-100）",
"16.修改经验（0-100）",
"17.修改等级（0-100）",
"18.修改魔法值（0-10000）",
"19.修改使用魔法时每次消耗的魔法值（0-100）",
"20.修改魔法伤害力（0-100）",
"21.修改命中率（0-100）",
"22.修改魔法防御力（0-100）",
"23.修改暴击率（0-100）",
"24.修改耐力（0-100）" ,
"25.退出"};

int menu(const char *[],int item_num);
void revise_nickname(char data[], const char* nickname);
void revise_value(char data[], int value, int pos, int byte_num, int max);
void input_value(int choice, char data[]);

int main()
{
	while (1)
	{
#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
		system("clear");
#elif defined(_WIN32) || defined(_WIN64)
		system("cls");
#endif

#elif defined(_MSC_VER)
		system("cls");
#endif

		int choice;
		char data[DATA_NUM + 1];

		fstream gamedat("game1.dat", ios::in | ios::out | ios::binary);
		if (!gamedat.is_open())
		{
			cerr << "文件打开失败" << endl;
			return -1;
		}

		//打印菜单选项,用户进行选择
		choice=menu(menu_items, ITEMS_NUM);

		//读取文件中的64个字符并存储在数组当中
		for (int i = 1; i <= DATA_NUM; i++)
		{
			data[i] = gamedat.get();
		}

		if (choice != 25)
		{
			input_value(choice, data);
		}
		else return 0;

		gamedat.seekp(0, ios::beg);

		for (int i = 1; i <= DATA_NUM; i++)
		{
			gamedat.put(data[i]);
		}

		gamedat.close();
	}

	return 0;
}

//该函数用于显示菜单选项供用户进行选择
int menu(const char *items[],int item_num)
{
	int choice;
	
	cout << "----------------------------------------------\n";
	cout << "请选择需要修改的内容:\n\n";

	for (int i = 0; i < item_num; i++)
	{
		cout << items[i] << endl;
	}
	cout << "请选择:";
	
	while (1)
	{
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > 25)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "输入不合法，请重新输入     ";
			continue;
		}
		else break;
	}

	return choice;
}

//该函数用于修改ID
void revise_nickname(char data[],const char* nickname)
{
	if (strlen(nickname) > 15)
	{
		cout << "昵称超过15个字符,3秒后返回主菜单..." << endl;

#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
		sleep(3);
#elif defined(_WIN32) || defined(_WIN64)
		Sleep(3000);
#endif

#elif defined(_MSC_VER)
		Sleep(3000);

#endif
		return;
	}
	else
	{
		strcpy(data, nickname);

		cout << "修改成功,3秒后返回主菜单..." << endl;

#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
		sleep(3);
#elif defined(_WIN32) || defined(_WIN64)
		Sleep(3000);
#endif

#elif defined(_MSC_VER)
		Sleep(3000);

#endif
		return;
	}
}

/*该函数用于修改某项具体值
  data:修改的数组对象
  value:修改的目标值
  pos:该项数据起始位置
  byte_num:该项数据所占的字节数
  max:该项数据允许修改的最大值*/
void revise_value(char data[], int value,int pos, int byte_num, int max)
{
	if (value > max || value < 0)
	{
		cout << "修改目标值非法,3秒后返回主菜单..." << endl;

#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
		sleep(3);
#elif defined(_WIN32) || defined(_WIN64)
		Sleep(3000);
#endif

#elif defined(_MSC_VER)
		Sleep(3000);

#endif
	}

	switch (byte_num)
	{
	case 1:
	{
		unsigned part1;
		part1 = value;
		data[pos] = part1;
		break;
	}

	case 2:
	{
		unsigned char part1, part2;
		part1 = value % 256;
		part2 = value / 256;

		data[pos] = part1;
		data[pos + 1] = part2;

		break;
	}

	case 4:
	{
		unsigned char part1, part2, part3, part4;
		part4 = value / 16777216;
		value %= 16777216;

		part3 = value / 65536;
		value %= 65536;

		part2 = value / 256;
		value %= 256;

		part1 = value;

		data[pos] = part1;
		data[pos + 1] = part2;
		data[pos + 2] = part3;
		data[pos + 3] = part4;

		break;
	}
	}

	cout << "修改成功,3秒后返回主菜单..." << endl;
#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
	sleep(3);
#elif defined(_WIN32) || defined(_WIN64)
	Sleep(3000);
#endif

#elif defined(_MSC_VER)
	Sleep(3000);

#endif
}

/*根据用户选择修改属性值
  供用户输入修改目标值，
  再用revise_value函数修改对应字节*/
void input_value(int choice,char data[])
{
#if defined(__GNUC__)

#if defined(__linux) || defined(__linux__)
	system("clear");
#elif defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif

#elif defined(_MSC_VER)
	system("cls");
#endif


	if (choice == 1)
	{
		char nickname[16];
		cout << "请输入修改的昵称：";
		cin >> nickname;

		revise_nickname(data, nickname);
		return;
	}

	int target;
	cout << "请输入修改的目标值：";
	cin >> target;

	switch (choice)
	{
	case 2:revise_value(data, target, HP, 2, 10000); break;
	case 3:revise_value(data, target, STRENGTH, 2, 10000); break;
	case 4:revise_value(data, target, CONSTITUTION, 2, 8192); break;
	case 5:revise_value(data, target, DEXTERITY, 2, 1024); break;
	case 6:revise_value(data, target, GOLD, 4, 100000000); break;
	case 7:revise_value(data, target, FAME, 4, 1000000); break;
	case 8:revise_value(data, target, CHARM, 4, 1000000); break;
	case 9:revise_value(data, target, MOVING_SPEED, 1, 100); break;
	case 10:revise_value(data, target, ATTACK_SPEED, 1, 100); break;
	case 11:revise_value(data, target, ATTACK_RANGE, 1, 100); break;
	case 12:revise_value(data, target, ATTACK_POWER, 2, 2000); break;
	case 13:revise_value(data, target, DEFENSE_FORCE, 2, 2000); break;
	case 14:revise_value(data, target, AGILITY, 1, 100); break;
	case 15:revise_value(data, target, IQ, 1, 100); break;
	case 16:revise_value(data, target, EXP, 1, 100); break;
	case 17:revise_value(data, target, LEVEL, 1, 100); break;
	case 18:revise_value(data, target, MP, 2, 10000); break;
	case 19:revise_value(data, target, COST_MANA, 1, 100); break;
	case 20:revise_value(data, target, MAGIC_DAMAGE, 1, 100); break;
	case 21:revise_value(data, target, HIT_RATE, 1, 100); break;
	case 22:revise_value(data, target, MAGIC_DAMAGE, 1, 100); break;
	case 23:revise_value(data, target, CRIT_RATE, 1, 100); break;
	case 24:revise_value(data, target, ENDURANCE, 1, 100); break;
	}

}
  