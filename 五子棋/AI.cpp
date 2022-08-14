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
	Sleep(1000);	//��װ˼��
	chess_kind_t t = chess->getPlayerFlag() ? Chess_Black : Chess_White;	//�ж���������
	chess->chessDown(&pos, t);
}

void AI::calculateScore()
{
	/*
	* ���ֹ���
	*			����	����
	* ��2		 10		 10
	* ��3		 30		 25
	* ��3		 40		 50
	* ��4		 60		 55
	* ��4		200		10000
	* ��5	   20000    30000
	*/
	//û�п������壡����

	int size = chess->getGradeSize();

	//������������
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			scoreMap[i][j] = 0;
		}
	}

	int personNum = 0;	//��ң����壩�ж��ٸ�����������
	int aiNum = 0;		//ai�����壩�ж��ٸ�����������
	int emptyNum = 0;	//�÷����Ͽհ�λ�ĸ���

	//��ÿ������м���
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{

			if (chess->getChessData(row, col))	//����õ��Ѿ�����������
				continue;

			//��������
			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0)
						continue;
					if (y == 0 && x != 1)		//��������ᷴ���жϣ�����ֻ��(-1,-1)(-1,0)(1,0)(0,-1)�ĸ������ж�
						continue;

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//��������ڴ�λ������
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

					//�����ڷ��������
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

					//���ּ���
					if (personNum == 1)	//��2	
					{
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2)
					{
						if (emptyNum == 1)	//��3
						{
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2)	//��3
						{
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3)
					{
						if (emptyNum == 1)	//��4
						{
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2)	//��4
						{
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4)
					{
						scoreMap[row][col] += 20000;
					}

					//��������ڴ�λ������
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

					//�����ڷ��������
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

					//���ּ���
					if (aiNum == 0)
					{
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1)	//��2
					{
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2)	//��3
					{
						if(emptyNum==1)			//��3
							scoreMap[row][col] += 25;
						else if(emptyNum==2)		//��3
							scoreMap[row][col] += 50;
					}
					else if (aiNum == 3)	//��4
					{
						if (emptyNum == 1)			//��4
							scoreMap[row][col] += 55;
						else if (emptyNum == 2)		//��4
							scoreMap[row][col] += 10000;
					}
					else if (aiNum == 4)	//aiӮ��
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

	//ai�������м�
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

	//�ҵ��������ֵ������maxPoints
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

	//�������һ���������ĵ�
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
