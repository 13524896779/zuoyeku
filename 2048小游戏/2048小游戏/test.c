#include"game.h"
void game()
{
	//初始化4*4格子内数据
	//BoardCreate(board, Row, Col);
	//打印游戏界面
	PrintBoard(board, Row, Col);
	//实现按W键向上移动
	//Wup(board, Row, Col);
	//实现按S键向下移动
	//Sdown(board,Row,Col);
	//实现按A键向左移动
	//Aleft(board, Row, Col);
	//实现按D键向右移动
	//Dright(board,Row,Col);
	//实现通过WSAD选择上下左右
	ChooseMove(board, Row, Col);
	//在棋盘随机位置生成一个2
	TwoFind(board, Row, Col);
	over(board, Row, Col);
}
int main()
{
	srand((unsigned int)time(NULL));
	GameInte();
	BoardCreate(board, Row, Col);
	int a = 0;
	do
	{
		scanf("%d", &a);
		if (a == 1)
		{
			game();
		}
		else if (a == 0)
		{
			printf("退出游戏\n");
			break;
		}
		else
		{
			printf("输入错误,重新输入:\n");
		}
	} while (a);
	return 0;
}