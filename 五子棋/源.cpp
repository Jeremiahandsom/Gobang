#include<iostream>
#include"ChessGame.h"

using namespace std;

int main()
{
	Man man;
	Chess chess();
	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}