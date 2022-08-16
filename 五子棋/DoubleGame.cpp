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

		//�������˵�
		if (chess->getExitFlag())
		{
			chess->buttonDown(502, 634, 150, 35, "�������˵�");
			Sleep(500);
			break;
		}

		//����
		if (chess->getAdmitDefeat())
		{
			selfLose();
			break;
		}

		if (chess->checkOver())
		{
			break;
		}

		//���2����
		man2->go();

		if (chess->getExitFlag())
		{
			chess->buttonDown(502, 634, 150, 35, "�������˵�");
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
	chess->buttonDown(270, 634, 80, 35, "����");
	Sleep(500);
	initgraph(897, 895);
	mciSendString("play res/ʧ��.mp3", 0, 0, 0);
	loadimage(0, "res/ʧ��.jpg");
	_getch();
}
