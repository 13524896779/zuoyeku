#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

//游戏菜单
void GameInte()
{
	printf("**********************************\n");
	printf("--**--**- 游 戏  2 0 4 8 -**--**--\n");
	printf("**********************************\n");
	printf("***-*-*-*-*   1.start  *-*-*-*-***\n");
	printf("***-*-*-*-*   0.quit   *-*-*-*-***\n");
	printf("************----------************\n");
	printf("是否游玩?请输入>:");
}
//初始化4*4格子内数据
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
//在棋盘随机位置生成一个2
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
//打印游戏界面
void PrintBoard(int board[Row][Col], int row, int col)
{
	system("CLS");//清屏上一次的棋盘
	printf("\n");
	int i = 0;
	int j = 0;
	printf(" ----------2048 游戏----------\n");
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
	printf(" ----------2048 游戏----------\n");
}
//实现按W键向上移动
void Wup(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = row - 1; i > 0; i--)
	{
		for (j = col - 1; j >= 0; j--)//必须设成>=0,否则j失去了=0的情况,会导致第一列无法正常移动
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
//实现按S键向下移动
void Sdown(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row - 1; i++)//必须设置成<row - 1,防止while循环中越界访问
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
//实现按A键向左移动
void Aleft(int board[Row][Col], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = row - 1; i >= 0; i--)
	{
		for (j = col - 1; j > 0; j--)//必须设成>=0,否则j失去了=0的情况,会导致第一列无法正常移动
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
//实现按D键向右移动
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
//实现通过WSAD选择上下左右
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
		printf("你确定要退出游戏吗?\n");
		printf("如果退出请输入0,继续游戏请按任意键\n");
		int choose;
		scanf("%d", &choose);
		if (choose == 0)
		{
			printf("退出游戏\n");
			exit(0);
		}
		else
		{
			printf("返回游戏:\n");
			goto again;
		}
		break;
	}
	}
}
//游戏结束判断
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
		printf("对不起,格子已满,游戏到此为止了!!!\n");
		exit(0);
	}
}