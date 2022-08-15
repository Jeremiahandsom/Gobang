#include "Man.h"
#include"Chess.h"
#include<easyx.h>

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;	
	ChessPos pos;
	while (1)
	{
		msg = GetMouseMsg();	//��ȡ�������Ϣ

		//ͨ��chess���󣬵����ж������Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}

		//������������˵���ť��
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 502 && msg.x <= 652 && msg.y >= 634 && msg.y <= 669)
		{
			chess->exitToMenu();
			break;
		}
	}

	
	if (chess->getExitFlag()==false)		//����������˵��˾Ͳ�����
	{
		chess_kind_t ManChessKind = chess->getPlayerFlag() ? Chess_Black : Chess_White;

		chess->chessDown(&pos, ManChessKind);	//����
	}
}
