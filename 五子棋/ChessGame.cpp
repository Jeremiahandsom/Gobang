#include "ChessGame.h"
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

//渲染透明背景的putimage
void putimagePNG1(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//开始游戏
void ChessGame::play()
{
	initgraph(672, 672, EW_SHOWCONSOLE);   
	loadimage(0, "res/menu.png",0,0,true);  //开始菜单

	MOUSEMSG msg;
	bool playerFirst = true;
	while (1)
	{
		loadimage(0, "res/menu.png", 0, 0, true);  //开始菜单
		msg = GetMouseMsg();

		//人机对战
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 319 && msg.y>243 && msg.y < 330)
		{
			loadimage(0, "res/人机对战.png", 0, 0, true);
			Sleep(500);
			chess->init();
			if (playerFirst)
			{
				while (1)
				{
					//先由棋手下棋
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

		//人人对战
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 330 && msg.y>469 && msg.y < 552)
		{
			loadimage(0, "res/人人对战.png", 0, 0, true);
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
	}
}
