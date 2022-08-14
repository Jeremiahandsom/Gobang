#pragma once
#include<graphics.h>	//easyx头文件
#include<vector>

using namespace std;

struct ChessPos			//落子位置
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

//棋色
typedef enum
{
	Chess_White = -1,
	Chess_Black = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//棋盘初始化，加载棋盘图片资源，初始化相关数据
	void init();

	//判断点击是否有效，如果有效，保存位置到pos中
	bool clickBoard(int x, int y, ChessPos* pos);

	//在指定位置落子
	void chessDown(ChessPos* pos, chess_kind_t kind);

	//获取棋盘大小
	int getGradeSize();	

	//获取指定位置棋种类
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//检查棋局是否结束
	bool checkOver();			

	bool getPlayerFlag();

private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	int gradeSize;	//棋盘大小
	int margin_x;	//棋盘左边距
	int margin_y;	//棋盘顶边距
	float chessSize;

	vector<vector<int>> chessMap;	//当前棋局的棋子分布数据：0：空， 1：黑子， -1：白子

	bool playerFlag;//现在该谁下棋，true:黑棋走，false:白棋走

	void updateMap(ChessPos* pos);	//更新棋局的棋子分布

	bool checkWin();	//如果胜负已分，返回true,否则返回true   

	ChessPos lastPos;	//最近的落子点位置
};

