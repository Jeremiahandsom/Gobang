#include "Chess.h"

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;

    playerFlag = Chess_Black;

    for (int i = 0; i < gradeSize; i++)
    {
        vector<int>row;
        for (int j = 0; j < gradeSize; j++)
        {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}

void Chess::init()
{
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    return false;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
}

int Chess::getGradeSize()
{
    return 0;
}

int Chess::getChessData(ChessPos* pos)
{
    return 0;
}

int Chess::getChessData(int row, int col)
{
    return 0;
}

bool Chess::checkOver()
{
    return false;
}
