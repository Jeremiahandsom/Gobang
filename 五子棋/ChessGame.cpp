#include "ChessGame.h"

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
	initgraph(672, 672);   
	loadimage(0, "res/menu.png",0,0,true);  //��ʼ�˵�
	//mciSendString("play res/bg.mp3", 0, 0, 0);	//���ű�������

	MOUSEMSG msg;
	bool playerFirst = true;
	while (1)
	{
		loadimage(0, "res/menu.png", 0, 0, true);  //��ʼ�˵�
		msg = GetMouseMsg();

		//�˻���ս
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 319 && msg.y>243 && msg.y < 330)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/�˻���ս.png", 0, 0, true);
			Sleep(500);
			chess->init();
			if (playerFirst)
			{
				while (1)
				{
					//������������
					man->go();
					if (chess->checkOver())
					{
						playerFirst = true;
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
			else
			{
				while (1)
				{
					ai->go();
					if (chess->checkOver())
					{
						playerFirst = false;
						break;
					}

					man->go();
					if (chess->checkOver())
					{
						playerFirst = true;
						break;
					}
				}
			}
		}

		//���˶�ս
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 330 && msg.y>469 && msg.y < 552)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/���˶�ս.png", 0, 0, true);
			Sleep(500);
			chess->init();
			while (1)
			{
				man->go();
				if (chess->checkOver())
				{
					break;
				}
			}
		}

		//�˳�����
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 417 && msg.x < 531 && msg.y>493 && msg.y < 594)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/�˳�.png", 0, 0, true);
			Sleep(500);
			closegraph();
			break;
		}
	}
}
