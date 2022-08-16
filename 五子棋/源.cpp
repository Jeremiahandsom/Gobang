#include<iostream>
#include"ChessGame.h"
#include"DoubleGame.h"

using namespace std;

int main()
{
	initgraph(672, 672);
	loadimage(0, "res/menu.png", 0, 0, true);  //开始菜单
	//mciSendString("play res/bg.mp3", 0, 0, 0);	//播放背景音乐

	MOUSEMSG msg;
	while (1)
	{
		loadimage(0, "res/menu.png", 0, 0, true);  //开始菜单
		msg = GetMouseMsg();

		//人机对战
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 319 && msg.y>243 && msg.y < 330)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/人机对战.png", 0, 0, true);
			Sleep(500);

			Man man;
			Chess chess(15, 41, 43, 42);
			AI ai;
			ChessGame game(&man, &ai, &chess);

			game.play();
		}

		//人人对战
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 330 && msg.y>469 && msg.y < 552)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/人人对战.png", 0, 0, true);
			Sleep(500);

			Man man1;
			Man man2;
			Chess chess(15, 41, 43, 42);
			DoubleGame game(&man1, &man2, &chess);

			game.play();
		}

		//退出按键
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 417 && msg.x < 531 && msg.y>493 && msg.y < 594)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/退出.png", 0, 0, true);
			Sleep(500);
			closegraph();
			break;
		}
	}
	return 0;
}