#include"game.h"
void game()
{
	//��ʼ��4*4����������
	//BoardCreate(board, Row, Col);
	//��ӡ��Ϸ����
	PrintBoard(board, Row, Col);
	//ʵ�ְ�W�������ƶ�
	//Wup(board, Row, Col);
	//ʵ�ְ�S�������ƶ�
	//Sdown(board,Row,Col);
	//ʵ�ְ�A�������ƶ�
	//Aleft(board, Row, Col);
	//ʵ�ְ�D�������ƶ�
	//Dright(board,Row,Col);
	//ʵ��ͨ��WSADѡ����������
	ChooseMove(board, Row, Col);
	//���������λ������һ��2
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
			printf("�˳���Ϸ\n");
			break;
		}
		else
		{
			printf("�������,��������:\n");
		}
	} while (a);
	return 0;
}