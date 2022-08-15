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
	}

	//printf("%d,%d\n", pos.row, pos.col);

	chess_kind_t ManChessKind =  chess->getPlayerFlag() ? Chess_Black : Chess_White;

	chess->chessDown(&pos, ManChessKind);	//����
}
