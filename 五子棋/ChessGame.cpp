#include "ChessGame.h"
#include<conio.h>

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

//开始游戏
void ChessGame::play()
{
	bool playerFirst = true;
	while (1)
	{
		chess->init();
		man->resetRegretNum();	
		bool backToMenu = false;

		//玩家先下
		if(playerFirst)
		{
			while (1)
			{
				man->go();

				//返回主菜单
				if (chess->getExitFlag())
				{
					backToMenu = true;
					chess->buttonDown(502, 634, 150, 35, "返回主菜单");
					Sleep(500);
					break;
				}

				//认输
				if (chess->getAdmitDefeat())
				{
					playerFirst = !playerFirst;
					selfLose();
					break;
				}

				if (chess->checkOver())
				{
					playerFirst = !playerFirst;
					break;
				}

				ai->go();
				if (chess->checkOver())
				{
					playerFirst = !playerFirst;
					break;
				}
			}
		}
	
		// 由AI先下棋
		else		
		{
			while (1)
			{
				ai->go();
				if (chess->checkOver())
				{
					playerFirst = !playerFirst;
					break;
				}

				man->go();

				//返回主菜单
				if (chess->getExitFlag())
				{
					backToMenu = true;
					chess->buttonDown(502, 634, 150, 35, "返回主菜单");
					Sleep(500);
					break;
				}

				//认输
				if (chess->getAdmitDefeat())
				{
					playerFirst = !playerFirst;
					selfLose();
					break;
				}

				if (chess->checkOver())
				{
					playerFirst = !playerFirst;
					break;
				}
			}
		}
		if (backToMenu)
			break;
	}
}


void ChessGame::selfLose()
{
	chess->buttonDown(270, 634, 80, 35, "认输");
	Sleep(500);
	initgraph(897, 895);
	mciSendString("play res/失败.mp3", 0, 0, 0);
	loadimage(0, "res/失败.jpg");
	_getch();
}
