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
			mciSendString("play res/select.mp3", 0, 0, 0);
			chess->buttonDown(502, 634, 150, 35, "返回主菜单");
			HWND window = GetHWnd();	//获取窗口句柄
			int isBack = MessageBox(window, "是否确认返回主菜单", "提示", MB_OKCANCEL);
			if (isBack == IDOK)
			{
				mciSendString("play res/select.mp3", 0, 0, 0);
				chess->exitToMenu();
				break;
			}
			else if (isBack == IDCANCEL)
			{
				chess->button(502, 634, 150, 35, "返回主菜单");
				mciSendString("play res/select.mp3", 0, 0, 0);
			}
		}

		//点击认输按钮
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 270 && msg.x <= 350 && msg.y >= 634 && msg.y <= 669)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			chess->buttonDown(270, 634, 80, 35, "认输");
			HWND window = GetHWnd();	//获取窗口句柄
			int isSelfDefeat = MessageBox(window, "是否确认认输", "提示", MB_OKCANCEL);
			if (isSelfDefeat == IDOK)
			{
				mciSendString("play res/select.mp3", 0, 0, 0);
				chess->selfDefeat();
				break;
			}
			else if(isSelfDefeat==IDCANCEL)
			{
				chess->button(270, 634, 80, 35, "认输");
				mciSendString("play res/select.mp3", 0, 0, 0);
			}
		}

		//点击悔棋按钮
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 40 && msg.x <= 120 && msg.y >= 634 && msg.y <= 669)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			chess->buttonDown(40, 634, 80, 35, "悔棋");
			HWND window = GetHWnd();	//获取窗口句柄
			if (regretNum < 3)
			{
				int isRegret = MessageBox(window, "是否确认悔棋", "提示", MB_OKCANCEL);
				if (isRegret == IDOK)
				{
					mciSendString("play res/select.mp3", 0, 0, 0);
					chess->regret();
					regretNum++;
				}
				else if (isRegret == IDCANCEL)
				{
					mciSendString("play res/select.mp3", 0, 0, 0);
				}
			}
			else
			{
				MessageBox(window, "您已悔棋超过3次，不可继续悔棋", "警告", MB_OK);
			}
			chess->button(40, 634, 80, 35, "悔棋");
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

		chess->updateManLastPos(pos);	//记录玩家最近落子位置
	}
}

void Man::resetRegretNum()
{
	regretNum = 0;
}

