#include "AI.h"
#include"ChessGame.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int>row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);	//假装思考
	chess_kind_t t = chess->getPlayerFlag() ? Chess_Black : Chess_White;	//判断下哪种棋
	chess->chessDown(&pos, t);
}

void AI::calculateScore()
{
	/*
	* 评分规则：
	*			黑棋	白棋
	* 连2		 10		 10
	* 死3		 30		 25
	* 活3		 40		 50
	* 死4		 60		 55
	* 活4		200		10000
	* 连5	   20000    30000
	*/
	//没有考虑跳冲！！！

	int size = chess->getGradeSize();

	//评分数组清零
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			scoreMap[i][j] = 0;
		}
	}

	int personNum = 0;	//玩家（黑棋）有多少个连续的棋子
	int aiNum = 0;		//ai（白棋）有多少个连续的棋子
	int emptyNum = 0;	//该方向上空白位的个数

	//对每个点进行计算
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{

			if (chess->getChessData(row, col))	//如果该点已经有子则跳过
				continue;

			//各个方向
			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0)
						continue;
					if (y == 0 && x != 1)		//由于下面会反向判断，这里只对(-1,-1)(-1,0)(1,0)(0,-1)四个方向判断
						continue;

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//如果黑棋在此位置落子
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
							personNum++;
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}

					//黑棋在反方向计算
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
							personNum++;
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}

					//评分计算
					if (personNum == 1)	//连2	
					{
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2)
					{
						if (emptyNum == 1)	//死3
						{
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2)	//活3
						{
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3)
					{
						if (emptyNum == 1)	//死4
						{
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2)	//活4
						{
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4)
					{
						scoreMap[row][col] += 20000;
					}

					//如果白棋在此位置落子
					emptyNum = 0;
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
							aiNum++;
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}

					//白棋在反方向计算
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
							aiNum++;
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}

					//评分计算
					if (aiNum == 0)
					{
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1)	//连2
					{
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2)	//连3
					{
						if(emptyNum==1)			//死3
							scoreMap[row][col] += 25;
						else if(emptyNum==2)		//活3
							scoreMap[row][col] += 50;
					}
					else if (aiNum == 3)	//连4
					{
						if (emptyNum == 1)			//死4
							scoreMap[row][col] += 55;
						else if (emptyNum == 2)		//活4
							scoreMap[row][col] += 10000;
					}
					else if (aiNum == 4)	//ai赢了
					{
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	calculateScore();

	vector<ChessPos>maxPoints;
	int maxScore = 0;
	int size = chess->getGradeSize();

	//ai先手下中间
	bool AiFirst = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (chess->getChessData(i, j) != 0)
			{
				AiFirst = false;
				break;
			}
		}
	}
	if(AiFirst)
		return ChessPos(size / 2, size / 2);

	//找到所有最大值，放入maxPoints
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col) == 0)
			{
				if (scoreMap[row][col] > maxScore)
				{
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore)
				{
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	//随机返回一个分数最大的点
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
