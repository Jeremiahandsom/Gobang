#include "Man.h"

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

		//通过chess对象，调用判断落子是否有效
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}
	}

	//printf("%d,%d\n", pos.row, pos.col);

	chess->chessDown(&pos, Chess_Black);	//落子
}
