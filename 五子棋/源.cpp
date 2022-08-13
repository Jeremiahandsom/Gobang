#include<iostream>
#include"ChessGame.h"

using namespace std;

int main()
{
	Man man;
	Chess chess(15,41,43,42);
	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}