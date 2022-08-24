#include "Man.h"
#include"Chess.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;	
	ChessPos pos;
	while (1)
	{
		msg = GetMouseMsg();	//��ȡ�������Ϣ

		//������������˵���ť��
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 502 && msg.x <= 652 && msg.y >= 634 && msg.y <= 669)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			chess->buttonDown(502, 634, 150, 35, "�������˵�");
			HWND window = GetHWnd();	//��ȡ���ھ��
			int isBack = MessageBox(window, "�Ƿ�ȷ�Ϸ������˵�", "��ʾ", MB_OKCANCEL);
			if (isBack == IDOK)
			{
				mciSendString("play res/select.mp3", 0, 0, 0);
				chess->exitToMenu();
				break;
			}
			else if (isBack == IDCANCEL)
			{
				chess->button(502, 634, 150, 35, "�������˵�");
				mciSendString("play res/select.mp3", 0, 0, 0);
			}
		}

		//������䰴ť
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 270 && msg.x <= 350 && msg.y >= 634 && msg.y <= 669)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			chess->buttonDown(270, 634, 80, 35, "����");
			HWND window = GetHWnd();	//��ȡ���ھ��
			int isSelfDefeat = MessageBox(window, "�Ƿ�ȷ������", "��ʾ", MB_OKCANCEL);
			if (isSelfDefeat == IDOK)
			{
				mciSendString("play res/select.mp3", 0, 0, 0);
				chess->selfDefeat();
				break;
			}
			else if(isSelfDefeat==IDCANCEL)
			{
				chess->button(270, 634, 80, 35, "����");
				mciSendString("play res/select.mp3", 0, 0, 0);
			}
		}

		//������尴ť
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 40 && msg.x <= 120 && msg.y >= 634 && msg.y <= 669)
		{
			mciSendString("play res/select.mp3", 0, 0, 0);
			chess->buttonDown(40, 634, 80, 35, "����");
			HWND window = GetHWnd();	//��ȡ���ھ��
			if (regretNum < 3)
			{
				int isRegret = MessageBox(window, "�Ƿ�ȷ�ϻ���", "��ʾ", MB_OKCANCEL);
				if (isRegret == IDOK)
				{
					mciSendString("play res/select.mp3", 0, 0, 0);
					chess->regret();
					regretNum++;
				}
				else if (isRegret == IDCANCEL)
				{
					mciSendString("play res/select.mp3", 0, 0, 0);
				}
			}
			else
			{
				MessageBox(window, "���ѻ��峬��3�Σ����ɼ�������", "����", MB_OK);
			}
			chess->button(40, 634, 80, 35, "����");
		}
		//ͨ��chess���󣬵����ж������Ƿ���Ч
		else if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}

	}

	if (!chess->getExitFlag() && !chess->getAdmitDefeat())		//����������˵��˻�����Ͳ�����
	{
		chess_kind_t ManChessKind = chess->getPlayerFlag() ? Chess_Black : Chess_White;

		chess->chessDown(&pos, ManChessKind);	//����

		chess->updateManLastPos(pos);	//��¼����������λ��
	}
}

void Man::resetRegretNum()
{
	regretNum = 0;
}

