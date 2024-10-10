#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#define Row 4
#define Col 4
int board[Row][Col];
//游戏菜单
void GameInte();

//4*4格内数据初始化
void BoardCreate(char board[Row][Col], int row, int col);

//在棋盘随机位置生成一个2
void TwoFind(char board[Row][Col], int row, int col);

//打印游戏界面
void PrintBoard(char board[Row][Col], int row, int col);

//实现按W键向上移动
void Wup(char board[Row][Col], int row, int col);

//实现按S键向下移动
void Sdown(int board[Row][Col], int row, int col);

//实现按A键向左移动
void Aleft(int board[Row][Col], int row, int col);

//实现按D键向右移动
void Dright(int board[Row][Col], int row, int col);

//实现通过WSAD选择上下左右
void ChooseMove(int board[Row][Col], int row, int col);

//判断游戏是否结束
void over(int board[Row][Col], int row, int col);