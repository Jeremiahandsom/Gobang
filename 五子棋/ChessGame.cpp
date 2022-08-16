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

//��ʼ��Ϸ
void ChessGame::play()
{
	bool playerFirst = true;
	while (1)
	{
		chess->init();
		man->resetRegretNum();	
		bool backToMenu = false;

		//�������
		if(playerFirst)
		{
			while (1)
			{
				man->go();

				//�������˵�
				if (chess->getExitFlag())
				{
					backToMenu = true;
					chess->buttonDown(502, 634, 150, 35, "�������˵�");
					Sleep(500);
					break;
				}

				//����
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
	
		// ��AI������
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

				//�������˵�
				if (chess->getExitFlag())
				{
					backToMenu = true;
					chess->buttonDown(502, 634, 150, 35, "�������˵�");
					Sleep(500);
					break;
				}

				//����
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
	chess->buttonDown(270, 634, 80, 35, "����");
	Sleep(500);
	initgraph(897, 895);
	mciSendString("play res/ʧ��.mp3", 0, 0, 0);
	loadimage(0, "res/ʧ��.jpg");
	_getch();
}
