#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#define Row 4
#define Col 4
int board[Row][Col];
//��Ϸ�˵�
void GameInte();

//4*4�������ݳ�ʼ��
void BoardCreate(char board[Row][Col], int row, int col);

//���������λ������һ��2
void TwoFind(char board[Row][Col], int row, int col);

//��ӡ��Ϸ����
void PrintBoard(char board[Row][Col], int row, int col);

//ʵ�ְ�W�������ƶ�
void Wup(char board[Row][Col], int row, int col);

//ʵ�ְ�S�������ƶ�
void Sdown(int board[Row][Col], int row, int col);

//ʵ�ְ�A�������ƶ�
void Aleft(int board[Row][Col], int row, int col);

//ʵ�ְ�D�������ƶ�
void Dright(int board[Row][Col], int row, int col);

//ʵ��ͨ��WSADѡ����������
void ChooseMove(int board[Row][Col], int row, int col);

//�ж���Ϸ�Ƿ����
void over(int board[Row][Col], int row, int col);