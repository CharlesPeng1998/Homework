#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "90-b0.h"
using namespace std;

int main()
{
	char input;
	char btm[10];//back-to-menu
	int x, y;
	
	while (1)
	{
		cout << "-----------------------------------" << endl;
		cout << "1.命令行找出可合并项并标识（非递归）" << endl;
		cout << "2.命令行找出可合并项并标识（递归）" << endl;
		cout << "3.命令行完成一次合成（分步骤显示）" << endl;
		cout << "4.命令行完整版（分步骤显示）" << endl;
		cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
		cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
		cout << "7.伪图形界面下用箭头键选择当前色块" << endl;
		cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
		cout << "9.伪图形界面完整版" << endl;
		cout << "0.退出" << endl;
		cout << "-----------------------------------" << endl;
		cout << "[请选择0-9]";

		setcursor(CURSOR_VISIBLE_HALF);
		input = _getch();

		
		if (input == '0')
		{
			cout << endl << endl << endl << endl << endl;
			return 0;
		}

		else if (input == '1')
		{
			int col, row;
			system("cls");
			input_row_col(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			ori_matrix(rand_matrix, mark_matrix, row, col);
			print_rmatrix(rand_matrix, row, col);
			check_mark1(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			print_mmatrix(mark_matrix, row, col);
			print_color_matrix(rand_matrix, mark_matrix, row, col);

			cout << endl << "本小题结束，请输入End继续...";
			getxy(x, y);
			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;

		}

		else if (input == '2')
		{
			int col, row;
			system("cls");
			input_row_col(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			ori_matrix(rand_matrix, mark_matrix, row, col);
			print_rmatrix(rand_matrix, row, col);
			check_mark2(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			print_mmatrix(mark_matrix, row, col);
			print_color_matrix(rand_matrix, mark_matrix, row, col);

			cout << endl << "本小题结束，请输入End继续...";
			getxy(x, y);
			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;

		}

		else if (input == '3')
		{
			int col, row, goal;
			char confirm;

			system("cls");
			input_rcg(row, col, goal);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num, score;

			ori_matrix(rand_matrix, mark_matrix, row, col);
			print_rmatrix(rand_matrix, row, col);

			check_mark1(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			print_mmatrix(mark_matrix, row, col);
			print_color_matrix(rand_matrix, mark_matrix, row, col);
			//询问用户是否继续操作并得到反馈
			cout << "请确认是否把相邻的相同值合并到" << input_alpha << input_num << "中<Y/N/Q>: ";
			while (confirm = _getch())
			{
				if (confirm == 'y' || confirm == 'Y')
				{
					cout << endl;
					score = combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

					cout << "本次得分: " << score << "  " << "总得分: " << score << "  " << "合成目标: " << goal << endl << endl;
					cout << "按回车键进行数组下落除0操作...";
					//忽略除回车以外所有输入
					while (_getch() != '\r')
						;

					bubble_up(rand_matrix, row, col);
					ori_mmatrix(mark_matrix, row, col);
					cout << endl;
					print_color_zero(rand_matrix, row, col);

					cout << "按回车键进行新值填充...";
					while (_getch() != '\r')
						;

					fill_rmatrix(rand_matrix, mark_matrix, row, col);

					cout << endl << "新值填充后的数组<不同色标识>: " << endl;
					print_color_matrix2(rand_matrix, mark_matrix, row, col, int(input_alpha - 65), input_num);

					if (end_check(rand_matrix, row, col))
					{
						cout << "无可合成项，游戏结束..." << endl;
					}

					cout << endl << "本小题结束，请输入End继续...";
					getxy(x, y);
					cin >> btm;

					while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
					{
						cout << "输入错误，请重新输入";
						gotoxy(x, y);
						cin >> btm;
					}

					system("cls");
					break;
				}
				else if (confirm == 'n' || confirm == 'N' || confirm == 'q' || confirm == 'Q')
				{
					cout << endl << "本小题结束，请输入End继续...";
					getxy(x, y);
					cin >> btm;

					while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
					{
						cout << "输入错误，请重新输入";
						gotoxy(x, y);
						cin >> btm;
					}

					system("cls");
					break;
				}
				else;
			}
			continue;
		}

		else if (input == '4')
		{
			int col, row, goal;
			//用于接收用户反馈并决定继续，重新输入以及退出游戏
			char confirm='y';

			system("cls");
			input_rcg(row, col, goal);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num, score,total_score=0;

			//初始化数组（随机填充）
			ori_matrix(rand_matrix, mark_matrix, row, col);

			while (confirm == 'y' || confirm == 'Y')
			{
				//每轮回合之前初始化一次标志矩阵
				ori_mmatrix(mark_matrix, row, col);
				//打印当前数组
				print_rmatrix(rand_matrix, row, col);
				
				while (1)
				{
					//接收用户输入矩阵坐标并检查能否合成
					check_mark1(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
					//打印标记矩阵
					print_mmatrix(mark_matrix, row, col);
					//打印选定连续区域上色矩阵
					print_color_matrix(rand_matrix, mark_matrix, row, col);

					//询问用户是否继续操作并得到反馈
					cout << "请确认是否把相邻的相同值合并到" << input_alpha << input_num << "中<Y/N/Q>: ";
					
					//仅接收输入Y/N/Q 或 y/n/q
					while (confirm = _getch())
					{
						if (confirm == 'Y' || confirm == 'y' || confirm == 'N' || confirm == 'n' || confirm == 'Q' || confirm == 'q') break;
						else;
					}

					//如果输入为Y或y，则继续进行合成操作
					if (confirm == 'Y' || confirm == 'y')
					{
						cout << endl;
						score = combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
						total_score += score;

						cout << "本次得分: " << score << "  " << "总得分: " << total_score << "  " << "合成目标: " << goal << endl << endl;
						cout << "按回车键进行数组下落除0操作...";
						//忽略除回车以外所有输入
						while (_getch() != '\r')
							;

						bubble_up(rand_matrix, row, col);
						ori_mmatrix(mark_matrix, row, col);
						cout << endl;
						print_color_zero(rand_matrix, row, col);

						cout << "按回车键进行新值填充...";
						while (_getch() != '\r')
							;

						fill_rmatrix(rand_matrix, mark_matrix, row, col);

						cout << endl << "新值填充后的数组<不同色标识>: " << endl;
						print_color_matrix2(rand_matrix, mark_matrix, row, col, int(input_alpha - 65), input_num);
						
						//检查是否还有可合成项，若无则游戏结束
						if (end_check(rand_matrix, row, col))
						{
							cout << "无可合成项，按回车键结束游戏...";
							while (_getch() != '\r')
									;
							confirm = 'q';
							break;
						}

						cout << "本次合成结束，按回车键继续新的一次合成...";
						if (win_check(rand_matrix,row,col,goal))
						{
							cout << endl;
							setcolor(COLOR_BLACK, COLOR_HPINK);
							cout << "已经合成到" << goal << endl;
							setcolor();
							cout << "按回车键向更高目标进发...";

							goal++;
						}

						while (_getch() != '\r')
							;
						break;

					}
					//如果输入为N或n，则用户重新输入矩阵坐标
					else if (confirm == 'N' || confirm == 'n')
					{
						ori_mmatrix(mark_matrix, row, col);
						continue;
					}
					//如果输入为Q或q，则退出游戏，返回菜单
					else if (confirm == 'Q' || confirm == 'q')
					{
						system("cls");
						break;
					}
				}

			}

		}

		else if (input == '5')
		{
			int col, row;
			system("cls");
			input_row_col(row, col);

			setconsoleborder(35 + (col - 5) * 6, 22 + (row - 5) * 3);
			//打印边框
			print_frame(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化数组（随机填充）
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//打印数组表格
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 6, 2 + i * 3);
					Sleep(100);
				}
				
			}

			cout << endl << endl << endl;
			getxy(x, y);
			gotoxy(0, 0);
			cout << "屏幕当前设置为: " << 22 + (row - 5) * 3 << "行" << 35 + (col - 5) * 6 << "列";
			gotoxy(x, y);
			
			
			cout<< "本小题结束，请输入End继续...";
			getxy(x, y);
			
			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}

		else if (input == '6')
		{
			int col, row;
			system("cls");
			input_row_col(row, col);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化数组（随机填充）
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//打印数组表格
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
					Sleep(100);
				}

			}

			cout << endl << endl << endl;
			getxy(x, y);
			gotoxy(0, 0);
			cout << "屏幕当前设置为: " << 26 + (row - 5) * 4 << "行" << 43 + (col - 5) * 8 << "列";
			gotoxy(x, y);


			cout << "本小题结束，请输入End继续...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}
		
		else if (input == '7')
		{
			int col, row;
			//当前所原则方块的行列
			int curr_row, curr_col;


			system("cls");
			input_row_col(row, col);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化数组（随机填充）
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//打印数组表格
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
					Sleep(100);
				}

			}

			cout << endl << endl << endl;
			getxy(x, y);
			gotoxy(0, 0);
			cout << "屏幕当前设置为: " << 26 + (row - 5) * 4 << "行" << 43 + (col - 5) * 8 << "列";
			gotoxy(x, y);

			//进行方块移动时隐藏光标，否则影响效果
			setcursor(CURSOR_INVISIBLE);
			move(rand_matrix,row,col,curr_row, curr_col);
			setcursor(CURSOR_VISIBLE_HALF);

			gotoxy(0, row * 4+2);
			cout << "本小题结束，请输入End继续...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}

		else if (input == '8')
		{
			//当前所原则方块的行列
			int curr_row=0, curr_col=0;
			//选择方块上一次所在的方块行列
			int last_row = 0, last_col = 0;
			//记录分数
			int score = 0;

			//两个字符用来接收用户输入的方向键
			char move1, move2;

			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化数组（随机填充）
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//打印数组表格
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
					Sleep(100);
				}

			}
		
			gotoxy(0, 0);
			cout << "屏幕当前设置为: " << 26 + (row - 5) * 4 << "行" << 43 + (col - 5) * 8 << "列";
			
			gotoxy(0, row * 4 + 2);
			cout << "方向键移动，回车键选择";
			
			//进行方块移动时隐藏光标，否则影响效果
			setcursor(CURSOR_INVISIBLE);

			print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
			
			//以下为接收用户按键进行操作的部分
			while (move1 = _getch())
			{
				gotoxy(0, row * 4 + 2);
				cout << "                                     ";
				gotoxy(0, row * 4 + 2);
				cout << "方向键移动，回车键选择";
				
				if (move1 == '\r')
				{
					//将选定方块周围的同值方块选定
					if (!check_mark3(rand_matrix, mark_matrix, row, col, curr_row, curr_col)) continue;
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < col; j++)
						{
							if (mark_matrix[i][j]=='*') print_chosen(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
						}
					}
					
					gotoxy(0, row * 4 + 2);
					cout << "                                     ";
					gotoxy(0, row * 4 + 2);
					cout << "方向键移动并取消当前选择，回车键合成";

					move1 = _getch();
					if (move1 == '\r')
					{
						//若再次输入回车，则选定表格的值加一，其他被选表格消失
						_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score);
						
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (mark_matrix[i][j] == '*') print_blank(2 + j * 8, 2 + i * 4);
							}
						}
						
						//制造合并之后选择方块频闪的特效
						print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
						
						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "合成完成，回车键下落0";

						while (_getch() != '\r') ;
						
						//处理方块下落
						_bubble_up(rand_matrix, row, col);

						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "下落完成，回车键填充新值";

						while (_getch() != '\r');
						
						//填充方块
						ori_mmatrix(mark_matrix, row, col);
						fill_rmatrix(rand_matrix, mark_matrix, row, col);

						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								Sleep(50);
								if (mark_matrix[i][j] == '*') print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
							}
						}

						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "本次合成完成，按C进行下一次合成";

						while (_getch() != 'c' && _getch() != 'C');
						
						break;

					}
					else
					{
						move2 = _getch();
						
						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "方向键移动，回车键选择";
						
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (mark_matrix[i][j] == '*') print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
							}
						}
						ori_mmatrix(mark_matrix, row, col);
						
						_move(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, move1, move2);
						continue;
					}
				}
				else
				{
					move2 = _getch();
					_move(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, move1, move2);
					continue;
				}
			}
			setcursor(CURSOR_VISIBLE_HALF);

			gotoxy(0, row * 4 + 2);
			cout << "                                     ";
			gotoxy(0, row * 4 + 2);
			cout << "本小题结束，请输入End继续...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}

		else if (input == '9')
		{
			//记录分数
			int score = 0,total_score = 0;

			//两个字符用来接收用户输入的方向键
			char move1, move2;

			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化数组（随机填充）
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//打印数组表格
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
					Sleep(100);
				}

			}
			
			gotoxy(0, 0);
			cout << "屏幕当前设置为: " << 26 + (row - 5) * 4 << "行" << 43 + (col - 5) * 8 << "列";

			//进行方块移动时隐藏光标，否则影响效果
			setcursor(CURSOR_INVISIBLE);

			while (1)
			{
				gotoxy(0, row * 4 + 2);
				cout << "                                     ";
				gotoxy(0, row * 4 + 2);
				cout << "方向键移动，回车键选择";
				
				//当前所原则方块的行列
				int curr_row = 0, curr_col = 0;
				//选择方块上一次所在的方块行列
				int last_row = 0, last_col = 0;

				print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

				//以下为接收用户按键进行操作的部分
				while (move1 = _getch())
				{
					gotoxy(0, row * 4 + 2);
					cout << "                                     ";
					gotoxy(0, row * 4 + 2);
					cout << "方向键移动，回车键选择";

					if (move1 == '\r')
					{
						//将选定方块周围的同值方块选定
						if (!check_mark3(rand_matrix, mark_matrix, row, col, curr_row, curr_col)) continue;
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (mark_matrix[i][j] == '*') print_chosen(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
							}
						}

						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "方向键移动并取消当前选择，回车键合成";

						move1 = _getch();
						if (move1 == '\r')
						{
							//若再次输入回车，则选定表格的值加一，其他被选表格消失
							_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score);
							total_score += score;//计算得分

							gotoxy(0, 0);
							cout << "                                          ";
							gotoxy(0, 0);
							cout << "本次得分：" << score << ' ' << "总分：" << total_score << ' ' << "合成目标：" << goal;

							for (int i = 0; i < row; i++)
							{
								for (int j = 0; j < col; j++)
								{
									if (mark_matrix[i][j] == '*') print_blank(2 + j * 8, 2 + i * 4);
								}
							}

							//制造合并之后选择方块频闪的特效
							print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

							//处理方块下落
							_bubble_up(rand_matrix, row, col);

							//填充方块
							ori_mmatrix(mark_matrix, row, col);
							fill_rmatrix(rand_matrix, mark_matrix, row, col);

							for (int i = 0; i < row; i++)
							{
								for (int j = 0; j < col; j++)
								{
									if (mark_matrix[i][j] == '*')
									{
										Sleep(50);
										print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
									}
								}
							}
							ori_mmatrix(mark_matrix, row, col);

							if (win_check(rand_matrix, row, col, goal))
							{
								gotoxy(0, row * 4 + 2);
								cout << "                                     ";
								gotoxy(0, row * 4 + 2);
								setcolor(0, COLOR_HYELLOW);
								cout << "已经合成到" << goal << ',' << "按回车向更高目标进发";
								setcolor();
								goal++;

								while (_getch() != '\r');

								gotoxy(0, 0);
								cout << "                                          ";
								gotoxy(0, 0);
								cout << "本次得分：" << score << ' ' << "总分：" << total_score << ' ' << "合成目标：" << goal;
							}

							break;
						}
						else
						{
							move2 = _getch();

							gotoxy(0, row * 4 + 2);
							cout << "                                     ";
							gotoxy(0, row * 4 + 2);
							cout << "方向键移动，回车键选择";

							for (int i = 0; i < row; i++)
							{
								for (int j = 0; j < col; j++)
								{
									if (mark_matrix[i][j] == '*') print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
								}
							}
							ori_mmatrix(mark_matrix, row, col);

							_move(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, move1, move2);
							continue;
						}
					}
					else
					{
						move2 = _getch();
						_move(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, move1, move2);
						continue;
					}
				}

				if (end_check(rand_matrix, row, col))
				{
					setcolor(0, COLOR_HRED);
					gotoxy(0, row * 4 + 2);
					cout << "                                     ";
					gotoxy(0, row * 4 + 2);
					cout << "无可合成项，游戏结束";
					setcolor();
					break;
				}
				else continue;
			}

			gotoxy(0, row * 4 + 2);
			cout << "                              ";
			gotoxy(0, row * 4 + 2);
			cout << "本小题结束，请输入End继续...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "输入错误，请重新输入";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}

		else
		{
			system("cls");
			continue;
		}
	}

	return 0;		
}
