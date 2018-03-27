#pragma once

void mark1(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col);
void mark2(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col);

void input_row_col(int &row, int &col);
void ori_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10],int row, int col);
void print_rmatrix(int (*rand_matrix)[10],int row,int col);
void check_mark1(int(*rand_matrix)[10],char (*mark_matrix)[10],int row,int col, char &input_alpha, int &input_num);
void check_mark2(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num);
void print_mmatrix(char(*mark_matrix)[10], int row, int col);
void print_color_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
void input_rcg(int &row, int &col, int &goal);
int combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num);
void bubble_up(int(*rand_matrix)[10],int row, int col);
void print_color_zero(int(*rand_matrix)[10], int row, int col);
void print_color_matrix2(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int cord_x, int cord_y);
void fill_rmatrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
void ori_mmatrix(char(*mark_matrix)[10], int row, int col);
bool end_check(int(*rand_matrix)[10], int row, int col);
bool win_check(int(*rand_matrix)[10], int row, int col,int &goal);
void print_frame(int row, int col);
void print_unicode(const char *str, const int bg_color, const int fg_color, const int n);
void print_table(int value, int cord_x, int cord_y);
void print_fullframe(int row, int col);
void print_chosen(int value, int cord_x, int cord_y);
void move(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col);
void go_up(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col);
void go_down(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col);
void go_left(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col);
void go_right(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col);
bool check_mark3(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col);
void _move(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col,char move1 , char move2);
void _combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col, int &score);
void print_blank(int cord_x, int cord_y);
void print_shiny(int value, int cord_x, int cord_y);
void fall(int(*rand_matrix)[10], int cord_row, int cord_col);
void _bubble_up(int(*rand_matrix)[10], int row, int col);