#pragma once
#include<graphics.h>	//easyxͷ�ļ�
#include<vector>

using namespace std;

struct ChessPos			//����λ��
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

//��ɫ
typedef enum
{
	Chess_White = -1,
	Chess_Black = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//���̳�ʼ������������ͼƬ��Դ����ʼ���������
	void init();

	//�жϵ���Ƿ���Ч�������Ч������λ�õ�pos��
	bool clickBoard(int x, int y, ChessPos* pos);

	//��ָ��λ������
	void chessDown(ChessPos* pos, chess_kind_t kind);

	//��ȡ���̴�С
	int getGradeSize();	

	//��ȡָ��λ��������
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//�������Ƿ����
	bool checkOver();			

	bool getPlayerFlag();

private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	int gradeSize;	//���̴�С
	int margin_x;	//������߾�
	int margin_y;	//���̶��߾�
	float chessSize;

	vector<vector<int>> chessMap;	//��ǰ��ֵ����ӷֲ����ݣ�0���գ� 1�����ӣ� -1������

	bool playerFlag;//���ڸ�˭���壬true:�����ߣ�false:������

	void updateMap(ChessPos* pos);	//������ֵ����ӷֲ�

	bool checkWin();	//���ʤ���ѷ֣�����true,���򷵻�true   

	ChessPos lastPos;	//��������ӵ�λ��
};

