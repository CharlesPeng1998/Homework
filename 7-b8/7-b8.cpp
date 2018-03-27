/* 1751367 计2 彭健聪*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */
#include <ctime>
using namespace std;

/* 允许定义常变量/宏定义，但不允许定义全局变量 */
#define HEART 3
#define DIAMOND 4
#define CLU 5
#define SPADE 6

/* 可以添加自己需要的函数 */

/* 打印某个玩家的牌面信息，如果是地主，后面加标记 */
int print(const char *prompt, const int landlord, const unsigned long long player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	unsigned long long card = player;
	
	
	cout << prompt;

	/*将64位变量的前五十二位分成十三份，分别代表不同的牌面数值
	每份中的四位由低位到高位分别代表C D H S四种花色*/
	for (int i = 3; i < 16; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			/*从低位开始逐位检查，若值为1则该牌存在，
			打印后进行右移位运算，以便于检查下一位*/
			if (card & 1)
			{
				switch (j)
				{
				case 0:cout << char(CLU); break;
				case 1:cout << char(DIAMOND); break;
				case 2:cout << char(HEART); break;
				case 3:cout << char(SPADE); break;
				}

				switch (i)
				{
				case 10:cout << 'T'; break;
				case 11:cout << 'J'; break;
				case 12:cout << 'Q'; break;
				case 13:cout << 'K'; break;
				case 14:cout << 'A'; break;
				case 15:cout << 2; break;
				default:cout << i; break;
				}
				cout << ' ';	
			}

			card = card >> 1;
		}
	}

	//检查是否有小王，大王
	if (card & 1) cout << "BJ ";
	card = card >> 1;
	if (card & 1) cout << "RJ ";

	//若该玩家为地主，则需打印出来
	if (landlord) cout << "<地主>";

	cout << endl;

	return 0;
}

int deal(unsigned long long *player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	int random;//随机数
	int landlord;

	/*用于发牌的牌堆，某位为1说明该牌仍存在于牌堆中,
	              否则已被分发出去*/
	unsigned long long orig_card = 0xFFFFFFFFFFFFFFFF;

	srand((unsigned int)(time(0)));

	for (int i = 0; i < 17; i++)
	{
		//随机抽牌给甲玩家
		while (1)
		{
			random = rand() % 54;
			//检查随机的牌是否已经分发出去
			if (orig_card & (unsigned long long)(pow(2, random)))
			{
				orig_card -= (unsigned long long)(pow(2, random));
				player[0] += (unsigned long long)(pow(2, random));
				break;
			}
			else continue;
		}

		//随机抽牌给乙玩家
		while (1)
		{
			random = rand() % 54;
			//检查随机的牌是否已经分发出去
			if (orig_card & (unsigned long long)(pow(2, random)))
			{
				orig_card -= (unsigned long long)(pow(2, random));
				player[1] += (unsigned long long)(pow(2, random));
				break;
			}
			else continue;
		}

		//随机抽牌给丙玩家
		while (1)
		{
			random = rand() % 54;
			//检查随机的牌是否已经分发出去
			if (orig_card & (unsigned long long)(pow(2, random)))
			{
				orig_card -= (unsigned long long)(pow(2, random));
				player[2] += (unsigned long long)(pow(2, random));
				break;
			}
			else continue;
		}

		cout << "第" << i + 1 << "轮结束：" << endl;
		
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 0, player[1]);
		print("丙的牌：", 0, player[2]);
	}

	while (1)
	{
		cout << endl << "请选择一个地主[0-2]:";
		cin >> landlord;

		if (cin.fail() || landlord<0 || landlord >2)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			continue;
		}
		else break;
	}

	player[landlord] += orig_card;//将剩余的牌给地主

	return landlord;
}

/* main函数，不准修改 */
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", landlord == 0, player[0]);
	print("乙的牌：", landlord == 1, player[1]);
	print("丙的牌：", landlord == 2, player[2]);

	return 0;
}
