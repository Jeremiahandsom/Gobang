#pragma once
#include"Chess.h"

class Man
{
public:
	void init(Chess* chess);
	void go();

	void resetRegretNum();	//ÖØÖÃ»ÚÆå´ÎÊı
private:
	Chess* chess;
	int regretNum = 0;
};

