#pragma once
#include"Man.h"
#include"Chess.h"
class DoubleGame
{
public:
	DoubleGame(Man* man1, Man* man2, Chess* chess);
	void play();

private:
	Man* man1;
	Man* man2;
	Chess* chess;

	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	void selfLose();	//»œ ‰¡˜≥Ã
};

