#pragma once
#include"Chess.h"

class Man
{
public:
	void init(Chess* chess);
	void go();

	void resetRegretNum();	//���û������
private:
	Chess* chess;
	int regretNum = 0;
};

