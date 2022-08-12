#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
}

//开始游戏
void ChessGame::play()
{
	chess->init();
	while (1)
	{
		//先由棋手下棋
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}

		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
	}
}
