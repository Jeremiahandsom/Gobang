#include "Man.h"
#include"Chess.h"

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

		//������������˵���ť��
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 502 && msg.x <= 652 && msg.y >= 634 && msg.y <= 669)
		{
			chess->exitToMenu();
			break;
		}

		//������䰴ť
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 270 && msg.x <= 350 && msg.y >= 634 && msg.y <= 669)
		{
			chess->selfDefeat();
			break;
		}

		//ͨ��chess���󣬵����ж������Ƿ���Ч
		else if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}

	}

	
	if (!chess->getExitFlag() && !chess->getAdmitDefeat())		//����������˵��˻�����Ͳ�����
	{
		chess_kind_t ManChessKind = chess->getPlayerFlag() ? Chess_Black : Chess_White;

		chess->chessDown(&pos, ManChessKind);	//����
	}
}
