#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

//��Ϸ�˵�
void GameInte()
{
	printf("**********************************\n");
	printf("--**--**- �� Ϸ  2 0 4 8 -**--**--\n");
	printf("**********************************\n");
	printf("***-*-*-*-*   1.start  *-*-*-*-***\n");
	printf("***-*-*-*-*   0.quit   *-*-*-*-***\n");
	printf("************----------************\n");
	printf("�Ƿ�����?������>:");
}
//��ʼ��4*4����������
void BoardCreate(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = 0;
		}
	}
}
//���������λ������һ��2
void TwoFind(int board[Row][Col], int row, int col)
{
again:
	int a = rand() % row;
	int b = rand() % col;
	if (board[a][b] == 0)
	{
		board[a][b] = 2;
	}
	else
		goto again;
}
//��ӡ��Ϸ����
void PrintBoard(int board[Row][Col], int row, int col)
{
	system("CLS");//������һ�ε�����
	printf("\n");
	int i = 0;
	int j = 0;
	printf(" ----------2048 ��Ϸ----------\n");
	printf("-*-*-*-*-*- 0->exit -*-*-*-*-*- \n");
	printf("   +-----+-----+-----+-----+\n");
	for (i = 0; i < row; i++)
	{
		printf("   |");
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == 0)
				printf("     |");
			else
				printf("%4d |", board[i][j]);
		}
		printf("\n   +-----+-----+-----+-----+\n");
	}
	printf("w->up s->down a->left d->right\n");
	printf(" ----------2048 ��Ϸ----------\n");
}
//ʵ�ְ�W�������ƶ�
void Wup(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = row - 1; i > 0; i--)
	{
		for (j = col - 1; j >= 0; j--)//�������>=0,����jʧȥ��=0�����,�ᵼ�µ�һ���޷������ƶ�
		{
			while (board[i][j] != 0 && board[i - 1][j] == 0)
			{
				board[i - 1][j] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
	for (i = row - 1; i > 0; i--)
	{
		for (j = col - 1; j >= 0; j--)
		{
			while (board[i][j] == board[i - 1][j] && board[i][j] != 0 && board[i - 1][j] != 0)
			{
				board[i - 1][j] *= 2;
				board[i][j] = 0;
			}
		}
	}
	PrintBoard(board, Row, Col);
}
//ʵ�ְ�S�������ƶ�
void Sdown(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row - 1; i++)//�������ó�<row - 1,��ֹwhileѭ����Խ�����
	{
		for (j = 0; j < col; j++)
		{
			while (board[i][j] != 0 && board[i + 1][j] == 0)
			{
				board[i + 1][j] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
	for (i = 0; i < row - 1; i++)
	{
		for (j = 0; j < col; j++)
		{
			while (board[i][j] == board[i + 1][j] && board[i][j] != 0 && board[i + 1][j] != 0)
			{
				board[i + 1][j] *= 2;
				board[i][j] = 0;
			}
		}
	}
	PrintBoard(board, Row, Col);
}
//ʵ�ְ�A�������ƶ�
void Aleft(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = row - 1; i >= 0; i--)
	{
		for (j = col - 1; j > 0; j--)//�������>=0,����jʧȥ��=0�����,�ᵼ�µ�һ���޷������ƶ�
		{
			while (board[i][j] != 0 && board[i][j - 1] == 0)
			{
				board[i][j - 1] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
	for (i = row - 1; i >= 0; i--)
	{
		for (j = col - 1; j > 0; j--)
		{
			while (board[i][j] == board[i][j - 1] && board[i][j] != 0 && board[i][j - 1] != 0)
			{
				board[i][j - 1] *= 2;
				board[i][j] = 0;
			}
		}
	}
	PrintBoard(board, Row, Col);
}
//ʵ�ְ�D�������ƶ�
void Dright(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col - 1; j++)
		{
			while (board[i][j] != 0 && board[i][j + 1] == 0)
			{
				board[i][j + 1] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col - 1; j++)
		{
			while (board[i][j] == board[i][j + 1] && board[i][j] != 0 && board[i][j + 1] != 0)
			{
				board[i][j + 1] *= 2;
				board[i][j] = 0;
			}
		}
	}
	PrintBoard(board, Row, Col);
}
//ʵ��ͨ��WSADѡ����������
void ChooseMove(int board[Row][Col], int row, int col)
{
again:
	char a = getch();
	switch (a)
	{
	case 'W':
	case 'w':
		Wup(board, Row, Col);
		break;
	case 'S':
	case 's':
		Sdown(board, Row, Col);
		break;
	case 'A':
	case 'a':
		Aleft(board, Row, Col);
		break;
	case 'D':
	case 'd':
		Dright(board, Row, Col);
		break;
	case '0':
	{
		printf("��ȷ��Ҫ�˳���Ϸ��?\n");
		printf("����˳�������0,������Ϸ�밴�����\n");
		int choose;
		scanf("%d", &choose);
		if (choose == 0)
		{
			printf("�˳���Ϸ\n");
			exit(0);
		}
		else
		{
			printf("������Ϸ:\n");
			goto again;
		}
		break;
	}
	}
}
//��Ϸ�����ж�
void over(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	int sum = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] != 0)
				sum++;
		}
	}
	if (sum == row * col)
	{
		PrintBoard(board, Row, Col);
		printf("�Բ���,��������,��Ϸ����Ϊֹ��!!!\n");
		exit(0);
	}
}