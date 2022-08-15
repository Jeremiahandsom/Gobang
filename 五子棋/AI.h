#pragma once
#include"Chess.h"

class AI
{
public:
	void init(Chess* chess);
	void go();

private:
	Chess* chess;
	vector<vector<int>>scoreMap;
	chess_kind_t AiChessKind;		//AI的下棋种类

private:
	void calculateScore();
	ChessPos think();

};

