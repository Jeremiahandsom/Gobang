#include<iostream>
#include"ChessGame.h"
#include"DoubleGame.h"

using namespace std;

int main()
{
	initgraph(672, 672);
	loadimage(0, "res/menu.png", 0, 0, true);  //��ʼ�˵�
	//mciSendString("play res/bg.mp3", 0, 0, 0);	//���ű�������

	MOUSEMSG msg;
	HWND window = GetHWnd();	//��ȡ���ھ��
	while (1)
	{
		loadimage(0, "res/menu.png", 0, 0, true);  //��ʼ�˵�
		msg = GetMouseMsg();

		//�������
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 63 && msg.x < 413 && msg.y>99 && msg.y < 207)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			MessageBox(window, "ʲô��������ô֪�������Ǹ�˧�磿��", "���㷢���ˣ�", MB_OK);
		}

		//�˻���ս
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 319 && msg.y>243 && msg.y < 330)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/�˻���ս.png", 0, 0, true);
			Sleep(500);

			Man man;
			Chess chess(15, 41, 43, 42);
			AI ai;
			ChessGame gameWithAi(&man, &ai, &chess);

			gameWithAi.play();
		}

		//������ս
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 317 && msg.y>357 && msg.y < 443)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/������ս.png", 0, 0, true);
			Sleep(400);

			MessageBox(window, "�˹�����δ�����������ĵȴ�", "��ܰ��ʾ", MB_OK);
		}

		//���˶�ս
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 330 && msg.y>469 && msg.y < 552)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/���˶�ս.png", 0, 0, true);
			Sleep(500);

			Man man1;
			Man man2;
			Chess chess(15, 41, 43, 42);
			DoubleGame gameWithPlayer(&man1, &man2, &chess);

			gameWithPlayer.play();
		}

		//�˳�����
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 417 && msg.x < 531 && msg.y>493 && msg.y < 594)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/�˳�.png", 0, 0, true);
			Sleep(500);
			int isExit = MessageBox(window, "�Ƿ�ȷ���˳���", "��ʾ", MB_OKCANCEL);
			if (isExit == IDOK)
			{
				closegraph();
				break;
			}
		}
	}
	return 0;
}