#include "DoubleGame.h"
#include <conio.h>

DoubleGame::DoubleGame(Man* man1, Man* man2, Chess* chess)
{
	this->man1 = man1;
	this->man2 = man2;
	this->chess = chess;

	man1->init(chess);
	man2->init(chess);
}

void DoubleGame::play()
{
	chess->init();
	while (1)
	{
		man1->go();

		//返回主菜单
		if (chess->getExitFlag())
		{
			chess->buttonDown(502, 634, 150, 35, "返回主菜单");
			Sleep(500);
			break;
		}

		//认输
		if (chess->getAdmitDefeat())
		{
			selfLose();
			break;
		}

		if (chess->checkOver())
		{
			break;
		}

		//玩家2操作
		man2->go();

		if (chess->getExitFlag())
		{
			chess->buttonDown(502, 634, 150, 35, "返回主菜单");
			Sleep(500);
			break;
		}

		if (chess->getAdmitDefeat())
		{
			selfLose();
			break;
		}

		if (chess->checkOver())
		{
			break;
		}
	}
}

void DoubleGame::selfLose()
{
	chess->buttonDown(270, 634, 80, 35, "认输");
	Sleep(500);
	initgraph(897, 895);
	mciSendString("play res/失败.mp3", 0, 0, 0);
	loadimage(0, "res/失败.jpg");
	_getch();
}
