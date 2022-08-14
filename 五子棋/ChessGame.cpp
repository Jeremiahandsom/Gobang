#include "ChessGame.h"
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

//��Ⱦ͸��������putimage
void putimagePNG1(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//��ʼ��Ϸ
void ChessGame::play()
{
	initgraph(672, 672, EW_SHOWCONSOLE);   
	loadimage(0, "res/menu.png",0,0,true);  //��ʼ�˵�

	MOUSEMSG msg;
	bool playerFirst = true;
	while (1)
	{
		loadimage(0, "res/menu.png", 0, 0, true);  //��ʼ�˵�
		msg = GetMouseMsg();

		//�˻���ս
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 133 && msg.x < 319 && msg.y>243 && msg.y < 330)
		{
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
	}
}
