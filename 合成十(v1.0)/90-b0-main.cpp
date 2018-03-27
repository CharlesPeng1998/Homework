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
		cout << "1.�������ҳ��ɺϲ����ʶ���ǵݹ飩" << endl;
		cout << "2.�������ҳ��ɺϲ����ʶ���ݹ飩" << endl;
		cout << "3.���������һ�κϳɣ��ֲ�����ʾ��" << endl;
		cout << "4.�����������棨�ֲ�����ʾ��" << endl;
		cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" << endl;
		cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" << endl;
		cout << "7.αͼ�ν������ü�ͷ��ѡ��ǰɫ��" << endl;
		cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩" << endl;
		cout << "9.αͼ�ν���������" << endl;
		cout << "0.�˳�" << endl;
		cout << "-----------------------------------" << endl;
		cout << "[��ѡ��0-9]";

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

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			ori_matrix(rand_matrix, mark_matrix, row, col);
			print_rmatrix(rand_matrix, row, col);
			check_mark1(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			print_mmatrix(mark_matrix, row, col);
			print_color_matrix(rand_matrix, mark_matrix, row, col);

			cout << endl << "��С�������������End����...";
			getxy(x, y);
			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
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

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			ori_matrix(rand_matrix, mark_matrix, row, col);
			print_rmatrix(rand_matrix, row, col);
			check_mark2(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			print_mmatrix(mark_matrix, row, col);
			print_color_matrix(rand_matrix, mark_matrix, row, col);

			cout << endl << "��С�������������End����...";
			getxy(x, y);
			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
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

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num, score;

			ori_matrix(rand_matrix, mark_matrix, row, col);
			print_rmatrix(rand_matrix, row, col);

			check_mark1(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			print_mmatrix(mark_matrix, row, col);
			print_color_matrix(rand_matrix, mark_matrix, row, col);
			//ѯ���û��Ƿ�����������õ�����
			cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << input_alpha << input_num << "��<Y/N/Q>: ";
			while (confirm = _getch())
			{
				if (confirm == 'y' || confirm == 'Y')
				{
					cout << endl;
					score = combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

					cout << "���ε÷�: " << score << "  " << "�ܵ÷�: " << score << "  " << "�ϳ�Ŀ��: " << goal << endl << endl;
					cout << "���س����������������0����...";
					//���Գ��س�������������
					while (_getch() != '\r')
						;

					bubble_up(rand_matrix, row, col);
					ori_mmatrix(mark_matrix, row, col);
					cout << endl;
					print_color_zero(rand_matrix, row, col);

					cout << "���س���������ֵ���...";
					while (_getch() != '\r')
						;

					fill_rmatrix(rand_matrix, mark_matrix, row, col);

					cout << endl << "��ֵ���������<��ͬɫ��ʶ>: " << endl;
					print_color_matrix2(rand_matrix, mark_matrix, row, col, int(input_alpha - 65), input_num);

					if (end_check(rand_matrix, row, col))
					{
						cout << "�޿ɺϳ����Ϸ����..." << endl;
					}

					cout << endl << "��С�������������End����...";
					getxy(x, y);
					cin >> btm;

					while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
					{
						cout << "�����������������";
						gotoxy(x, y);
						cin >> btm;
					}

					system("cls");
					break;
				}
				else if (confirm == 'n' || confirm == 'N' || confirm == 'q' || confirm == 'Q')
				{
					cout << endl << "��С�������������End����...";
					getxy(x, y);
					cin >> btm;

					while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
					{
						cout << "�����������������";
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
			//���ڽ����û��������������������������Լ��˳���Ϸ
			char confirm='y';

			system("cls");
			input_rcg(row, col, goal);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num, score,total_score=0;

			//��ʼ�����飨�����䣩
			ori_matrix(rand_matrix, mark_matrix, row, col);

			while (confirm == 'y' || confirm == 'Y')
			{
				//ÿ�ֻغ�֮ǰ��ʼ��һ�α�־����
				ori_mmatrix(mark_matrix, row, col);
				//��ӡ��ǰ����
				print_rmatrix(rand_matrix, row, col);
				
				while (1)
				{
					//�����û�����������겢����ܷ�ϳ�
					check_mark1(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
					//��ӡ��Ǿ���
					print_mmatrix(mark_matrix, row, col);
					//��ӡѡ������������ɫ����
					print_color_matrix(rand_matrix, mark_matrix, row, col);

					//ѯ���û��Ƿ�����������õ�����
					cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << input_alpha << input_num << "��<Y/N/Q>: ";
					
					//����������Y/N/Q �� y/n/q
					while (confirm = _getch())
					{
						if (confirm == 'Y' || confirm == 'y' || confirm == 'N' || confirm == 'n' || confirm == 'Q' || confirm == 'q') break;
						else;
					}

					//�������ΪY��y����������кϳɲ���
					if (confirm == 'Y' || confirm == 'y')
					{
						cout << endl;
						score = combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
						total_score += score;

						cout << "���ε÷�: " << score << "  " << "�ܵ÷�: " << total_score << "  " << "�ϳ�Ŀ��: " << goal << endl << endl;
						cout << "���س����������������0����...";
						//���Գ��س�������������
						while (_getch() != '\r')
							;

						bubble_up(rand_matrix, row, col);
						ori_mmatrix(mark_matrix, row, col);
						cout << endl;
						print_color_zero(rand_matrix, row, col);

						cout << "���س���������ֵ���...";
						while (_getch() != '\r')
							;

						fill_rmatrix(rand_matrix, mark_matrix, row, col);

						cout << endl << "��ֵ���������<��ͬɫ��ʶ>: " << endl;
						print_color_matrix2(rand_matrix, mark_matrix, row, col, int(input_alpha - 65), input_num);
						
						//����Ƿ��пɺϳ����������Ϸ����
						if (end_check(rand_matrix, row, col))
						{
							cout << "�޿ɺϳ�����س���������Ϸ...";
							while (_getch() != '\r')
									;
							confirm = 'q';
							break;
						}

						cout << "���κϳɽ��������س��������µ�һ�κϳ�...";
						if (win_check(rand_matrix,row,col,goal))
						{
							cout << endl;
							setcolor(COLOR_BLACK, COLOR_HPINK);
							cout << "�Ѿ��ϳɵ�" << goal << endl;
							setcolor();
							cout << "���س��������Ŀ�����...";

							goal++;
						}

						while (_getch() != '\r')
							;
						break;

					}
					//�������ΪN��n�����û����������������
					else if (confirm == 'N' || confirm == 'n')
					{
						ori_mmatrix(mark_matrix, row, col);
						continue;
					}
					//�������ΪQ��q�����˳���Ϸ�����ز˵�
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
			//��ӡ�߿�
			print_frame(row, col);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ�����飨�����䣩
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//��ӡ������
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
			cout << "��Ļ��ǰ����Ϊ: " << 22 + (row - 5) * 3 << "��" << 35 + (col - 5) * 6 << "��";
			gotoxy(x, y);
			
			
			cout<< "��С�������������End����...";
			getxy(x, y);
			
			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
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

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ�����飨�����䣩
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//��ӡ������
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
			cout << "��Ļ��ǰ����Ϊ: " << 26 + (row - 5) * 4 << "��" << 43 + (col - 5) * 8 << "��";
			gotoxy(x, y);


			cout << "��С�������������End����...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}
		
		else if (input == '7')
		{
			int col, row;
			//��ǰ��ԭ�򷽿������
			int curr_row, curr_col;


			system("cls");
			input_row_col(row, col);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ�����飨�����䣩
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//��ӡ������
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
			cout << "��Ļ��ǰ����Ϊ: " << 26 + (row - 5) * 4 << "��" << 43 + (col - 5) * 8 << "��";
			gotoxy(x, y);

			//���з����ƶ�ʱ���ع�꣬����Ӱ��Ч��
			setcursor(CURSOR_INVISIBLE);
			move(rand_matrix,row,col,curr_row, curr_col);
			setcursor(CURSOR_VISIBLE_HALF);

			gotoxy(0, row * 4+2);
			cout << "��С�������������End����...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}

		else if (input == '8')
		{
			//��ǰ��ԭ�򷽿������
			int curr_row=0, curr_col=0;
			//ѡ�񷽿���һ�����ڵķ�������
			int last_row = 0, last_col = 0;
			//��¼����
			int score = 0;

			//�����ַ����������û�����ķ����
			char move1, move2;

			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ�����飨�����䣩
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//��ӡ������
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
					Sleep(100);
				}

			}
		
			gotoxy(0, 0);
			cout << "��Ļ��ǰ����Ϊ: " << 26 + (row - 5) * 4 << "��" << 43 + (col - 5) * 8 << "��";
			
			gotoxy(0, row * 4 + 2);
			cout << "������ƶ����س���ѡ��";
			
			//���з����ƶ�ʱ���ع�꣬����Ӱ��Ч��
			setcursor(CURSOR_INVISIBLE);

			print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
			
			//����Ϊ�����û��������в����Ĳ���
			while (move1 = _getch())
			{
				gotoxy(0, row * 4 + 2);
				cout << "                                     ";
				gotoxy(0, row * 4 + 2);
				cout << "������ƶ����س���ѡ��";
				
				if (move1 == '\r')
				{
					//��ѡ��������Χ��ֵͬ����ѡ��
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
					cout << "������ƶ���ȡ����ǰѡ�񣬻س����ϳ�";

					move1 = _getch();
					if (move1 == '\r')
					{
						//���ٴ�����س�����ѡ������ֵ��һ��������ѡ�����ʧ
						_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score);
						
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (mark_matrix[i][j] == '*') print_blank(2 + j * 8, 2 + i * 4);
							}
						}
						
						//����ϲ�֮��ѡ�񷽿�Ƶ������Ч
						print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
						
						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "�ϳ���ɣ��س�������0";

						while (_getch() != '\r') ;
						
						//����������
						_bubble_up(rand_matrix, row, col);

						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "������ɣ��س��������ֵ";

						while (_getch() != '\r');
						
						//��䷽��
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
						cout << "���κϳ���ɣ���C������һ�κϳ�";

						while (_getch() != 'c' && _getch() != 'C');
						
						break;

					}
					else
					{
						move2 = _getch();
						
						gotoxy(0, row * 4 + 2);
						cout << "                                     ";
						gotoxy(0, row * 4 + 2);
						cout << "������ƶ����س���ѡ��";
						
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
			cout << "��С�������������End����...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
				gotoxy(x, y);
				cin >> btm;
			}

			system("cls");
			continue;
		}

		else if (input == '9')
		{
			//��¼����
			int score = 0,total_score = 0;

			//�����ַ����������û�����ķ����
			char move1, move2;

			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);

			print_fullframe(row, col);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ�����飨�����䣩
			ori_matrix(rand_matrix, mark_matrix, row, col);

			//��ӡ������
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					print_table(rand_matrix[i][j], 2 + j * 8, 2 + i * 4);
					Sleep(100);
				}

			}
			
			gotoxy(0, 0);
			cout << "��Ļ��ǰ����Ϊ: " << 26 + (row - 5) * 4 << "��" << 43 + (col - 5) * 8 << "��";

			//���з����ƶ�ʱ���ع�꣬����Ӱ��Ч��
			setcursor(CURSOR_INVISIBLE);

			while (1)
			{
				gotoxy(0, row * 4 + 2);
				cout << "                                     ";
				gotoxy(0, row * 4 + 2);
				cout << "������ƶ����س���ѡ��";
				
				//��ǰ��ԭ�򷽿������
				int curr_row = 0, curr_col = 0;
				//ѡ�񷽿���һ�����ڵķ�������
				int last_row = 0, last_col = 0;

				print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

				//����Ϊ�����û��������в����Ĳ���
				while (move1 = _getch())
				{
					gotoxy(0, row * 4 + 2);
					cout << "                                     ";
					gotoxy(0, row * 4 + 2);
					cout << "������ƶ����س���ѡ��";

					if (move1 == '\r')
					{
						//��ѡ��������Χ��ֵͬ����ѡ��
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
						cout << "������ƶ���ȡ����ǰѡ�񣬻س����ϳ�";

						move1 = _getch();
						if (move1 == '\r')
						{
							//���ٴ�����س�����ѡ������ֵ��һ��������ѡ�����ʧ
							_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score);
							total_score += score;//����÷�

							gotoxy(0, 0);
							cout << "                                          ";
							gotoxy(0, 0);
							cout << "���ε÷֣�" << score << ' ' << "�ܷ֣�" << total_score << ' ' << "�ϳ�Ŀ�꣺" << goal;

							for (int i = 0; i < row; i++)
							{
								for (int j = 0; j < col; j++)
								{
									if (mark_matrix[i][j] == '*') print_blank(2 + j * 8, 2 + i * 4);
								}
							}

							//����ϲ�֮��ѡ�񷽿�Ƶ������Ч
							print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

							//����������
							_bubble_up(rand_matrix, row, col);

							//��䷽��
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
								cout << "�Ѿ��ϳɵ�" << goal << ',' << "���س������Ŀ�����";
								setcolor();
								goal++;

								while (_getch() != '\r');

								gotoxy(0, 0);
								cout << "                                          ";
								gotoxy(0, 0);
								cout << "���ε÷֣�" << score << ' ' << "�ܷ֣�" << total_score << ' ' << "�ϳ�Ŀ�꣺" << goal;
							}

							break;
						}
						else
						{
							move2 = _getch();

							gotoxy(0, row * 4 + 2);
							cout << "                                     ";
							gotoxy(0, row * 4 + 2);
							cout << "������ƶ����س���ѡ��";

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
					cout << "�޿ɺϳ����Ϸ����";
					setcolor();
					break;
				}
				else continue;
			}

			gotoxy(0, row * 4 + 2);
			cout << "                              ";
			gotoxy(0, row * 4 + 2);
			cout << "��С�������������End����...";
			getxy(x, y);

			cin >> btm;

			while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
			{
				cout << "�����������������";
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
