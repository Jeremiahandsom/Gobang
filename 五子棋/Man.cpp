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
		msg = GetMouseMsg();	//获取鼠标点击消息

		//点击“返回主菜单按钮”
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 502 && msg.x <= 652 && msg.y >= 634 && msg.y <= 669)
		{
			chess->exitToMenu();
			break;
		}

		//点击认输按钮
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 270 && msg.x <= 350 && msg.y >= 634 && msg.y <= 669)
		{
			chess->selfDefeat();
			break;
		}

		//通过chess对象，调用判断落子是否有效
		else if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}

	}

	
	if (!chess->getExitFlag() && !chess->getAdmitDefeat())		//如果返回主菜单了或认输就不下棋
	{
		chess_kind_t ManChessKind = chess->getPlayerFlag() ? Chess_Black : Chess_White;

		chess->chessDown(&pos, ManChessKind);	//落子
	}
}
