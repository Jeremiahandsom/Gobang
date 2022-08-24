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
	HWND window = GetHWnd();	//获取窗口句柄
	while (1)
	{
		loadimage(0, "res/menu.png", 0, 0, true);  //开始菜单
		msg = GetMouseMsg();

		//点击标题
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 63 && msg.x < 413 && msg.y>99 && msg.y < 207)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			MessageBox(window, "什么？！你怎么知道作者是个帅哥？？", "被你发现了！", MB_OK);
		}

		//人机对战
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 319 && msg.y>243 && msg.y < 330)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/人机对战.png", 0, 0, true);
			Sleep(500);

			Man man;
			Chess chess(15, 41, 43, 42);
			AI ai;
			ChessGame gameWithAi(&man, &ai, &chess);

			gameWithAi.play();
		}

		//联机对战
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 317 && msg.y>357 && msg.y < 443)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/联机对战.png", 0, 0, true);
			Sleep(400);

			MessageBox(window, "此功能尚未开发，请耐心等待", "温馨提示", MB_OK);
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
			DoubleGame gameWithPlayer(&man1, &man2, &chess);

			gameWithPlayer.play();
		}

		//退出按键
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 417 && msg.x < 531 && msg.y>493 && msg.y < 594)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			loadimage(0, "res/退出.png", 0, 0, true);
			Sleep(500);
			int isExit = MessageBox(window, "是否确认退出？", "提示", MB_OKCANCEL);
			if (isExit == IDOK)
			{
				closegraph();
				break;
			}
		}
	}
	return 0;
}