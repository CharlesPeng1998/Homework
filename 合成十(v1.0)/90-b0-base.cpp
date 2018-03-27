#define _CRT_SECURE_NO_WARNINGS
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

//���������Ǻ������ǵݹ�汾��
void mark1(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col)
{
	matrix2[cord_row][cord_col] = '*';
	bool stat=1;//���ڴ洢Ѱ����������һ���״̬
	int target = matrix1[cord_row][cord_col];

	while (stat)
	{
		stat = 0;
		for (int i = 0; i < Max_row; i++)
		{
			for (int j = 0; j < Max_col; j++)
			{
				if (matrix1[i][j] == target && matrix2[i][j] == '*')
				{
					if (i > 0 && matrix1[i - 1][j] == target && matrix2[i - 1][j] != '*')
					{
						matrix2[i - 1][j] = '*';
						stat = 1;
					}

					if (i < Max_row-1 && matrix1[i + 1][j] == target && matrix2[i + 1][j] != '*')
					{
						matrix2[i + 1][j] = '*';
						stat = 1;
					}

					if (j > 0 && matrix1[i][j-1] == target && matrix2[i][j-1] != '*')
					{
						matrix2[i][j-1] = '*';
						stat = 1;
					}

					if (j<Max_col-1 && matrix1[i][j+1] == target && matrix2[i][j+1] != '*')
					{
						matrix2[i][j+1] = '*';
						stat = 1;
					}
				}
			}
		}

		if (stat == 0) break;
	}
}
//���������Ǻ������ݹ�汾��
void mark2(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col)
{
	matrix2[cord_row][cord_col] = '*';

	if (cord_row > 0 && matrix1[cord_row - 1][cord_col] == matrix1[cord_row][cord_col] && matrix2[cord_row - 1][cord_col] != '*')
	{
		matrix2[cord_row - 1][cord_col] = '*';
		mark2(matrix1, matrix2, cord_row - 1, cord_col, Max_row, Max_col);
	}

	if (cord_row < Max_row - 1 && matrix1[cord_row + 1][cord_col] == matrix1[cord_row][cord_col] && matrix2[cord_row + 1][cord_col] != '*')
	{
		matrix2[cord_row + 1][cord_col] = '*';
		mark2(matrix1, matrix2, cord_row + 1, cord_col, Max_row, Max_col);
	}

	if (cord_col > 0 && matrix1[cord_row][cord_col - 1] == matrix1[cord_row][cord_col] && matrix2[cord_row][cord_col - 1] != '*')
	{
		matrix2[cord_row][cord_col - 1] = '*';
		mark2(matrix1, matrix2, cord_row, cord_col - 1, Max_row, Max_col);
	}

	if (cord_row <Max_col - 1 && matrix1[cord_row][cord_col + 1] == matrix1[cord_row][cord_col] && matrix2[cord_row][cord_col + 1] != '*')
	{
		matrix2[cord_row][cord_col + 1] = '*';
		mark2(matrix1, matrix2, cord_row, cord_col + 1, Max_row, Max_col);
	}
}
//�ú��������û�����������
void input_row_col(int &row, int &col)
{
	bool judge_row = 0, judge_col = 0;
	
	int curr_x;
	int curr_y; //������¼��ǰ����λ��

	getxy(curr_x, curr_y);//��ȡ��ǰ���λ�ã��Ա����������ʱ��귵����ԭ����λ��
	
	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);
		cout << "����������<5-8>: ";
		cin >> row;

		//���������Ƿ�Ϸ�����ͬ
		if (cin.fail() || row < 5 || row > 8)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_row = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//��������������ϴ����µĴ�����ʾ����ͬ

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);
		cout << "����������<5-10>: ";
		cin >> col;

		if (cin.fail() || col < 5 || col > 10)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_col = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);
}
//�ú�������������(�������ڳ�ʼ����䣩
void ori_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10],int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mark_matrix[i][j] = '0';
		}
	}

	srand((unsigned int)(time(0)));//�����������

	//1-3�ȸ���������
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			switch (rand() % 3)
			{
			case 0:rand_matrix[i][j] = 1; break;
			case 1:rand_matrix[i][j] = 2; break;
			case 2:rand_matrix[i][j] = 3; break;
			}
		}
	}

}
//�ú������ڴ�ӡ���������
void print_rmatrix(int(*rand_matrix)[10],int row, int col)
{
	cout << endl;
	cout << "��ǰ����:" << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			cout << "  " << rand_matrix[i][j];
		}
		cout << endl;
	}
}
//�ú������ڼ���û��ṩ�������겢�����������(�ǵݹ�汾��
void check_mark1(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	//�ж��Ƿ����������ֵͬ�Ľ��
	bool judge_value = 0;

	int curr_x, curr_y;
	

	while (judge_value != 1)
	{
		cout <<endl<< "������ĸ+������ʽ[��: c2]�����������: ";
		getxy(curr_x, curr_y);//�õ���ǰ����λ��

		bool judge_input = 0;

		while (judge_input != 1)
		{
			gotoxy(curr_x, curr_y);
			getchar();
			input_alpha = getchar();
			cin >> input_num;

			if (input_alpha >= 97) input_alpha -= 32;//������Сд��ĸ��������Ҫת��Ϊ��д��ĸ

			if (int(input_alpha - 65) > row - 1 || input_num > col - 1 || int(input_alpha - 65) < 0 || input_num < 0)
			{
				cout << "�����������������";
				gotoxy(curr_x, curr_y);
			}
			else judge_input = 1;
		}

		cout << "����Ϊ" << input_alpha << "��" << input_num << "��" << endl;

		//�����ĸ�if��������ж�ѡ��������Χ�Ƿ������ֵͬ
		if (int(input_alpha - 65) > 0 && rand_matrix[int(input_alpha - 65) - 1][input_num] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else if (int(input_alpha - 65) < row - 1 && rand_matrix[int(input_alpha - 65) + 1][input_num] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else if (input_num > 0 && rand_matrix[int(input_alpha - 65)][input_num - 1] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else if (input_num < col - 1 && rand_matrix[int(input_alpha - 65)][input_num + 1] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;

		if (judge_value == 1) mark1(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);
	}
}
//�ú������ڼ���û��ṩ�������겢�����������(�ݹ�汾��
void check_mark2(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	bool judge_value = 0;

	int curr_x, curr_y;
	//�ж��Ƿ����������ֵͬ�Ľ��

	while (judge_value != 1)
	{
		cout << "������ĸ+������ʽ[��: c2]�����������: ";
		getxy(curr_x, curr_y);//�õ���ǰ����λ��

		bool judge_input = 0;

		while (judge_input != 1)
		{
			gotoxy(curr_x, curr_y);
			getchar();
			input_alpha = getchar();
			cin >> input_num;

			if (input_alpha >= 97) input_alpha -= 32;//������Сд��ĸ��������Ҫת��Ϊ��д��ĸ

			if (int(input_alpha - 65) > row - 1 || input_num > col - 1 || int(input_alpha - 65) < 0 || input_num < 0)
			{
				cout << "�����������������";
				gotoxy(curr_x, curr_y);
			}
			else judge_input = 1;

		}

		cout << "����Ϊ" << input_alpha << "��" << input_num << "��" << endl;

		//�����ĸ�if��������ж�ѡ��������Χ�Ƿ������ֵͬ
		if (int(input_alpha - 65) > 0 && rand_matrix[int(input_alpha - 65) - 1][input_num] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else if (int(input_alpha - 65) < row - 1 && rand_matrix[int(input_alpha - 65) + 1][input_num] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else if (input_num > 0 && rand_matrix[int(input_alpha - 65)][input_num - 1] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else if (input_num < col - 1 && rand_matrix[int(input_alpha - 65)][input_num + 1] == rand_matrix[int(input_alpha - 65)][input_num])
		{
			judge_value = 1;
		}
		else cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;

		if (judge_value == 1) mark2(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);

	}
}
//�ú������ڴ�ӡ��Ǿ���
void print_mmatrix(char(*mark_matrix)[10], int row, int col)
{
	cout << endl << "���ҽ������:" << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			cout << "  " << mark_matrix[i][j];
		}
		cout << endl;
	}
}
//�ú������ڴ�ӡ��ɫ����
void print_color_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	cout << "��ǰ����:" << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*')
			{
				setcolor(COLOR_BLACK, COLOR_HPINK);
				cout << "  " << rand_matrix[i][j];
				setcolor();
			}
			else
			{
				cout << "  " << rand_matrix[i][j];
			}
		}
		cout << endl;
	}
}
//�ú��������û������������Լ�Ŀ��ֵ
void input_rcg(int &row, int &col, int &goal)
{
	bool judge_row = 0, judge_col = 0,judge_goal=0;

	int curr_x;
	int curr_y; //������¼��ǰ����λ��

	getxy(curr_x, curr_y);//��ȡ��ǰ���λ�ã��Ա����������ʱ��귵����ԭ����λ��

	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);
		cout << "����������<5-8>: ";
		cin >> row;

		//���������Ƿ�Ϸ�����ͬ
		if (cin.fail() || row < 5 || row > 8)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_row = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//��������������ϴ����µĴ�����ʾ����ͬ

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);
		cout << "����������<5-10>: ";
		cin >> col;

		if (cin.fail() || col < 5 || col > 10)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_col = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);

	while (!judge_goal)
	{
		gotoxy(curr_x, curr_y);
		cout << "������ϳ�Ŀ��<5-20>: ";
		cin >> goal;

		if (cin.fail() || goal < 5 || goal > 20)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_goal = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);
}
//�ú������ںϲ������㣬�Ʒ�
int combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	int score = 0;//��¼�û��÷�
	int target = rand_matrix[int(input_alpha - 65)][input_num];
		
	//�������������㲢��Ŀ������һ
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*')
			{
					rand_matrix[i][j] = 0;
					score += target * 3;
			}
		}
	}
	rand_matrix[int(input_alpha - 65)][input_num] = target + 1;

	print_color_matrix(rand_matrix, mark_matrix, row, col);

	return score;
}
//�ú������ڽ������������0����
void bubble_up(int(*rand_matrix)[10], int row, int col)
{
	int temp;

	for (int i = 0; i < col; i++)
	{
		for (int j = row-1; j>0; j--)
		{
			for (int k = row - 1; k > 0; k--)
			{
				if (rand_matrix[k][i] == 0)
				{
					temp = rand_matrix[k][i];
					rand_matrix[k][i] = rand_matrix[k - 1][i];
					rand_matrix[k - 1][i] = temp;
				}
			}
		}
	}
}
//�ú������ڴ�ӡ���������ͬɫ��ʶ����
void print_color_zero(int(*rand_matrix)[10],int row,int col)
{
	cout << "��0�������<��ͬɫ��ʶ>: " << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] == 0)
			{
				setcolor(COLOR_BLACK, COLOR_HPINK);
				cout << "  " << rand_matrix[i][j];
				setcolor();
			}
			else
			{
				cout << "  " << rand_matrix[i][j];
			}
		}
		cout << endl;
	}
}
//�ú������������󣨽���������������ÿ����0��ʹ�ã� �������˱�����λ�õĹ��ܣ��Ա���Ϊ���λ����ɫ��
void fill_rmatrix(int(*rand_matrix)[10], char(*mark_matrix)[10],int row, int col)
{
	int random;//���ڼ�¼�����

	//��������Ѱ�����ֵ
	int max = rand_matrix[0][0];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] > max) max = rand_matrix[i][j];
		}
	}

	//�������ֵ����������ֵĸ���
	if (max == 3 || max==0)
	{
		srand((unsigned int)(time(0)));//�����������

		//1-3�ȸ���������
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					switch (rand() % 3)
					{
					case 0:rand_matrix[i][j] = 1; break;
					case 1:rand_matrix[i][j] = 2; break;
					case 2:rand_matrix[i][j] = 3; break;
					}

					mark_matrix[i][j] = '*';
				}
			}
		}
	}

	else if (max == 4)
	{
		srand((unsigned int)(time(0)));//�����������

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 10;

					if (random >= 0 && random <= 2) rand_matrix[i][j] = 1;
					else if (random >= 3 && random <= 5) rand_matrix[i][j] = 2;
					else if (random >= 6 && random <= 8) rand_matrix[i][j] = 3;
					else rand_matrix[i][j] = 4;

					mark_matrix[i][j] = '*';
				}
			}
		}

	}

	else if (max == 5)
	{
		srand((unsigned int)(time(0)));//�����������

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 20;

					if (random >= 0 && random <= 4) rand_matrix[i][j] = 1;
					else if (random >= 5 && random <= 9) rand_matrix[i][j] = 2;
					else if (random >= 10 && random <= 14) rand_matrix[i][j] = 3;
					else if (random >= 15 && random <= 17) rand_matrix[i][j] = 4;
					else rand_matrix[i][j] = 5;

					mark_matrix[i][j] = '*';
				}
			}
		}
	}

	else if (max == 6)
	{
		srand((unsigned int)(time(0)));//�����������

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 20;

					if (random >= 0 && random <= 3) rand_matrix[i][j] = 1;
					else if (random >= 4 && random <= 7) rand_matrix[i][j] = 2;
					else if (random >= 8 && random <= 11) rand_matrix[i][j] = 3;
					else if (random >= 12 && random <= 15) rand_matrix[i][j] = 4;
					else if (random >= 16 && random <= 18) rand_matrix[i][j] = 5;
					else rand_matrix[i][j] = 6;

					mark_matrix[i][j] = '*';
				}
			}
		}
	}

	else
	{
		srand((unsigned int)(time(0)));//�����������

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand()%20;

					if (random >= 0 && random <= 15)
					{
						rand_matrix[i][j] = (rand() % (max - 3)) + 1;
					}
					else if (random >= 16 && random<=17) rand_matrix[i][j] = max-2;
					else if (random == 18) rand_matrix[i][j] = max-1;
					else rand_matrix[i][j] = max;

					mark_matrix[i][j] = '*';
				}
			}
		}
	}
}
//�ú�������Ϊ���������ɫ
void print_color_matrix2(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col,int cord_x,int cord_y)
{
	cout << "��ǰ����:" << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*')
			{
				setcolor(COLOR_BLACK, COLOR_HPINK);
				cout << "  " << rand_matrix[i][j];
				setcolor();
			}
			else
			{
				cout << "  " << rand_matrix[i][j];
			}
		}
		cout << endl;
	}
}
//�ú������ڱ�Ǿ���ĳ�ʼ��
void ori_mmatrix(char(*mark_matrix)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mark_matrix[i][j] = '0';
		}
	}
}
//�ú�������ÿ�غϽ��������Ƿ��ܹ�����������Ϸ��������ʾ��Ϸ����
bool end_check(int(*rand_matrix)[10], int row, int col)
{
	bool end = true;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i > 0 && rand_matrix[i - 1][j] == rand_matrix[i][j])
			{
				end = false;
			}
			else if (i < row - 1 && rand_matrix[i + 1][j] == rand_matrix[i][j])
			{
				end = false;
			}
			else if (j > 0 && rand_matrix[i][j - 1] == rand_matrix[i][j])
			{
				end = false;
			}
			else if (j < col - 1 && rand_matrix[i][j + 1] == rand_matrix[i][j])
			{
				end = false;
			}
			
			
		}
	}

	return end;
}
//�ú��������ж��Ƿ�ﵽ�ϳ�Ŀ��
bool win_check(int(*rand_matrix)[10], int row, int col,int &goal)
{
	bool win = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] == goal) win = true;
		}
	}

	return win;
}
//�ú������ڻ���αͼ���û�����ı߿�(�޷ָ��߰汾)
void print_frame(int row, int col)
{
	gotoxy(0, 1);
	//���������ӡ�ϱ߿�
	print_unicode("�X", COLOR_WHITE, COLOR_BLACK, 1);
	print_unicode("�T", COLOR_WHITE, COLOR_BLACK, col*3);
	print_unicode("�[", COLOR_WHITE, COLOR_BLACK, 1);

	//��ӡ���ұ߿�
	for (int i = 2; i < row*3+2; i++)
	{
		//showstr(0, i, "�U", COLOR_WHITE, COLOR_BLACK);
		print_unicode("�U", COLOR_WHITE, COLOR_BLACK, 1);
		for (int j = 0; j < col * 6; j++)
		{
			cout << ' ';
		}
		//showstr((col*3+1)*2, i, "�U", COLOR_WHITE, COLOR_BLACK);
		print_unicode("�U", COLOR_WHITE, COLOR_BLACK, 1);
		cout << endl;
		
	}
	
	//��ӡ�±߿�
	print_unicode("�^", COLOR_WHITE, COLOR_BLACK, 1);
	print_unicode("�T", COLOR_WHITE, COLOR_BLACK, col * 3);
	print_unicode("�a", COLOR_WHITE, COLOR_BLACK, 1);
}
//�ú������ڴ�ӡ����unicode�ַ�
void print_unicode(const char *str, const int bg_color, const int fg_color, const int n)
{
	const char *p;

	setcolor(bg_color, fg_color);
	
	for (int i = 0; i < n; i++)
	{
		for (p = str; *p; p++)
			putchar(*p);

		Sleep(10);
	}
	setcolor();
}
//�ú������ڴ�ӡ�������鷽�飨��ɫ�汾��
void print_table(int value, int cord_x, int cord_y)
{
	gotoxy(cord_x, cord_y);
	
	//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
	switch (value)
	{
	case 1:setcolor(COLOR_HWHITE, 0); break;
	case 2:setcolor(COLOR_HYELLOW, 0); break;
	case 3:setcolor(COLOR_HPINK, 0); break;
	case 4:setcolor(COLOR_HRED, 0); break;
	case 5:setcolor(COLOR_HCYAN, 0); break;
	case 6:setcolor(COLOR_HGREEN, 0); break;
	case 7:setcolor(COLOR_HBLUE, 0); break;
	case 8:setcolor(COLOR_HBLACK, 0); break;
	case 9:setcolor(COLOR_WHITE, 0); break;
	case 10:setcolor(COLOR_YELLOW, 0); break;
	case 11:setcolor(COLOR_PINK, 0); break;
	case 12:setcolor(COLOR_RED, 0); break;
	case 13:setcolor(COLOR_CYAN, 0); break;
	case 14:setcolor(COLOR_GREEN, 0); break;
	case 15:setcolor(COLOR_BLUE, 0); break;
	case 16:setcolor(COLOR_HBLUE, 0); break;
	case 17:setcolor(COLOR_HPINK, 0); break;
	case 18:setcolor(COLOR_RED, 0); break;
	case 19:setcolor(COLOR_HBLUE, 0); break;
	case 20:setcolor(COLOR_PINK, 0); break;

	}
	if (value < 10)
	{
		cout << "�X" << "�T" << "�[";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�U" << ' ' << value << "�U";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�^" << "�T" << "�a";
	}
	else
	{
		cout << "�X" << "�T" << "�[";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�U" << value << "�U";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�^" << "�T" << "�a";
	}

	setcolor();
}
//�ú������ڻ���αͼ���û�����ı߿�(�зָ��߰汾)
void print_fullframe(int row, int col)
{
	gotoxy(0, 1);
	//��ӡ�ϱ߿�
	print_unicode("�X", COLOR_WHITE, COLOR_BLACK, 1);
	
	for (int i = 0; i < col - 1; i++)
	{
		print_unicode("�T", COLOR_WHITE, COLOR_BLACK, 3);
		print_unicode("�h", COLOR_WHITE, COLOR_BLACK, 1);
	}
	
	print_unicode("�T", COLOR_WHITE, COLOR_BLACK, 3);
	print_unicode("�[", COLOR_WHITE, COLOR_BLACK, 1);

	//��ӡ���ұ߿�
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			print_unicode("�U", COLOR_WHITE, COLOR_BLACK, 1);
			
			for (int k = 0; k < col-1; k++)
			{
				print_unicode("      ", COLOR_WHITE, COLOR_BLACK, 1);
				print_unicode("��", COLOR_WHITE, COLOR_BLACK, 1);
			}
			print_unicode("      ", COLOR_WHITE, COLOR_BLACK, 1);
			
			print_unicode("�U", COLOR_WHITE, COLOR_BLACK, 1);
			cout << endl;
		}
		
		print_unicode("�c", COLOR_WHITE, COLOR_BLACK, 1);
		for (int j = 0; j < col-1; j++)
		{
			print_unicode("������", COLOR_WHITE, COLOR_BLACK, 1);
			print_unicode("��", COLOR_WHITE, COLOR_BLACK, 1);
		}
		print_unicode("������", COLOR_WHITE, COLOR_BLACK, 1);
		print_unicode("�f", COLOR_WHITE, COLOR_BLACK, 1);
		cout << endl;

	}

	for (int j = 0; j < 3; j++)
	{
		print_unicode("�U", COLOR_WHITE, COLOR_BLACK, 1);

		for (int k = 0; k < col - 1; k++)
		{
			print_unicode("      ", COLOR_WHITE, COLOR_BLACK, 1);
			print_unicode("��", COLOR_WHITE, COLOR_BLACK, 1);
		}
		print_unicode("      ", COLOR_WHITE, COLOR_BLACK, 1);

		print_unicode("�U", COLOR_WHITE, COLOR_BLACK, 1);
		cout << endl;
	}

	//��ӡ�±߿�
	print_unicode("�^", COLOR_WHITE, COLOR_BLACK, 1);

	for (int i = 0; i < col - 1; i++)
	{
		print_unicode("�T", COLOR_WHITE, COLOR_BLACK, 3);
		print_unicode("�k", COLOR_WHITE, COLOR_BLACK, 1);
	}

	print_unicode("�T", COLOR_WHITE, COLOR_BLACK, 3);
	print_unicode("�a", COLOR_WHITE, COLOR_BLACK, 1);
}
//�ú������ڴ�ӡ��ǰѡ��ı��
void print_chosen(int value, int cord_x, int cord_y)
{
	gotoxy(cord_x, cord_y);

	//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
	setcolor(COLOR_GREEN, COLOR_BLACK);
	
	if (value < 10)
	{
		cout << "�X" << "�T" << "�[";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�U" << ' ' << value << "�U";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�^" << "�T" << "�a";
	}
	else
	{
		cout << "�X" << "�T" << "�[";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�U" << value << "�U";
		getxy(cord_x, cord_y);
		gotoxy(cord_x - 6, cord_y + 1);
		cout << "�^" << "�T" << "�a";
	}

	setcolor();
}
//�ú������ڷ�����ƶ�ѡ�񷽿�
void move(int(*rand_matrix)[10],int row,int col,int &curr_row,int &curr_col)
{
	//�����ַ����������û�����ķ����
	char move1, move2;
	//��¼��ǰѡ��ķ��飬��ʼĬ��Ϊ��һ������
	curr_row = 0; curr_col = 0;
	//��¼��һ��ѡ��ķ���
	int last_row = 0, last_col = 0;

	print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

	while (move1 = _getch())
	{
		if (move1 == '\r') break;
		else
		{
			move2 = _getch();
			//���뷽���Ϊ��
			if (int(move1) == -32 && int(move2) == 72)
			{
				//����һ�������ӡ��ɫ
				if (curr_row == 0) curr_row = row - 1;
				else curr_row -= 1;

				print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
				//ԭ�����ӡԭɫ
				print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

				last_row = curr_row; last_col = curr_col;
			}

			else if (int(move1) == -32 && int(move2) == 80)
			{
				//����һ�������ӡ��ɫ
				if (curr_row == row - 1) curr_row = 0;
				else curr_row += 1;

				print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
				//ԭ�����ӡԭɫ
				print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

				last_row = curr_row; last_col = curr_col;
			}

			else if (int(move1) == -32 && int(move2) == 75)
			{
				//����һ�������ӡ��ɫ
				if (curr_col == 0) curr_col = col - 1;
				else curr_col -= 1;

				print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
				//ԭ�����ӡԭɫ
				print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

				last_row = curr_row; last_col = curr_col;
			}

			else if (int(move1) == -32 && int(move2) == 77)
			{
				//����һ�������ӡ��ɫ
				if (curr_col == col - 1) curr_col = 0;
				else curr_col += 1;

				print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
				//ԭ�����ӡԭɫ
				print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

				last_row = curr_row; last_col = curr_col;
			}

			else continue;
		}
	}

	
}
/*����Ϊ�б�Ҫ�����������ƶ��ֱ�����Ϊ�ĸ�����*/
void go_up(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	//����һ�������ӡ��ɫ
	if (curr_row == 0) curr_row = row - 1;
	else curr_row -= 1;

	print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
	//ԭ�����ӡԭɫ
	print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

	last_row = curr_row; last_col = curr_col;
}
void go_down(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	//����һ�������ӡ��ɫ
	if (curr_row == row - 1) curr_row = 0;
	else curr_row += 1;

	print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
	//ԭ�����ӡԭɫ
	print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

	last_row = curr_row; last_col = curr_col;
}
void go_left(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	//����һ�������ӡ��ɫ
	if (curr_col == 0) curr_col = col - 1;
	else curr_col -= 1;

	print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
	//ԭ�����ӡԭɫ
	print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

	last_row = curr_row; last_col = curr_col;
}
void go_right(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	//����һ�������ӡ��ɫ
	if (curr_col == col - 1) curr_col = 0;
	else curr_col += 1;

	print_chosen(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);
	//ԭ�����ӡԭɫ
	print_table(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4);

	last_row = curr_row; last_col = curr_col;
}
//�ú������ڼ���û�ѡ��ķ��鲢��ɫ��������
bool check_mark3(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col)
{
	bool judge_value = 0;
	
	//�����ĸ�if��������ж�ѡ��������Χ�Ƿ������ֵͬ
	if (curr_row > 0 && rand_matrix[curr_row - 1][curr_col] == rand_matrix[curr_row][curr_col])
	{
		judge_value = 1;
	}
	else if (curr_row < row - 1 && rand_matrix[curr_row + 1][curr_col] == rand_matrix[curr_row][curr_col])
	{
		judge_value = 1;
	}
	else if (curr_col > 0 && rand_matrix[curr_row][curr_col - 1] == rand_matrix[curr_row][curr_col])
	{
		judge_value = 1;
	}
	else if (curr_col < col - 1 && rand_matrix[curr_row][curr_col + 1] == rand_matrix[curr_row][curr_col])
	{
		judge_value = 1;
	}
	else
	{
		gotoxy(0, row * 4 + 2);
		setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "��Χ����ֵͬ��";
		setcolor();
		cout << "������ƶ����س���ѡ��";
	}

	if (judge_value == 1)
	{
		mark1(rand_matrix, mark_matrix, curr_row, curr_col, row, col);
		return judge_value;
	}
	else return judge_value;
}
//�ú������ڷ�����ƶ�ѡ�񷽿�(�޸İ棩
void _move(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col,char move1,char move2)
{
	if (int(move1) == -32 && int(move2) == 72)
	{
		go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col);
	}

	else if (int(move1) == -32 && int(move2) == 80)
	{
		//����һ�������ӡ��ɫ
		go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col);
	}

	else if (int(move1) == -32 && int(move2) == 75)
	{
		//����һ�������ӡ��ɫ
		go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col);
	}

	else if (int(move1) == -32 && int(move2) == 77)
	{
		//����һ�������ӡ��ɫ
		go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col);
	}
}
//�ú�������αͼ�ν���ĺϲ������㣬�Ʒ�
void _combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col,int &score)
{
	score = 0;
	int target = rand_matrix[curr_row][curr_col];

	//�������������㲢��Ŀ������һ
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*')
			{
				rand_matrix[i][j] = 0;
				score += target * 3;
			}
		}
	}
	rand_matrix[curr_row][curr_col] = target + 1;
}
//�ú������ڴ�ӡ�ո�
void print_blank(int cord_x, int cord_y)
{
	gotoxy(cord_x, cord_y);

	setcolor(COLOR_WHITE, COLOR_BLACK);
	
	cout << "  " << "  " << "  ";
	getxy(cord_x, cord_y);
	gotoxy(cord_x - 6, cord_y + 1);
	cout << "  " << ' ' << ' ' << "  ";
	getxy(cord_x, cord_y);
	gotoxy(cord_x - 6, cord_y + 1);
	cout << "  " << "  " << "  ";

	setcolor();
}
//�ú�����������ϲ�ʱƵ����Ч
void print_shiny(int value, int cord_x, int cord_y)
{
	for (int i = 0; i < 3; i++)
	
	{
		int X = cord_x, Y = cord_y;
		print_chosen(value, cord_x, cord_y);
		Sleep(100);
		//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
		print_table(value, cord_x, cord_y);
		Sleep(100);

	}
	setcolor();
}
//�ú�������ʹ��������һ��
void fall(int(*rand_matrix)[10], int cord_row, int cord_col)
{
	int target = rand_matrix[cord_row][cord_col];
	int cord_x = 2 + cord_col * 8;
	int cord_y = 3 + cord_row * 4;
	
	for (int i = 0; i < 3; i++)
	{
		print_blank(2 + cord_col * 8, 2 + cord_row * 4);
		print_table(target, cord_x, cord_y);

		cord_y++;
		Sleep(50);
	}

	print_blank(2 + cord_col * 8, 2 + cord_row * 4);
	gotoxy(cord_x, cord_row*4+5);
	
	setcolor(COLOR_WHITE, COLOR_BLACK);
	cout << "������";
	setcolor();
	print_table(target, cord_x, cord_y);
}
//�ú������ڷ������䣨ð��ԭ��
void _bubble_up(int(*rand_matrix)[10], int row, int col)
{
	int temp;

	for (int i = 0; i < col; i++)
	{
		for (int j = row - 1; j>0; j--)
		{
			for (int k = row - 1; k > 0; k--)
			{
				if (rand_matrix[k][i] == 0)
				{
					if (rand_matrix[k - 1][i] == 0)
					{
						temp = rand_matrix[k][i];
						rand_matrix[k][i] = rand_matrix[k - 1][i];
						rand_matrix[k - 1][i] = temp;
					}
					else
					{
						fall(rand_matrix, k - 1, i);
						
						temp = rand_matrix[k][i];
						rand_matrix[k][i] = rand_matrix[k - 1][i];
						rand_matrix[k - 1][i] = temp;
					}
				}
			}
		}
	}
}