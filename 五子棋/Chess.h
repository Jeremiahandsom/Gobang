#pragma once
#include<graphics.h>	//easyxͷ�ļ�
#include<vector>

using namespace std;

struct ChessPos			//����λ��
{
	int row;
	int col;
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

private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	int gradeSize;	//���̴�С
	int margin_x;	//������߾�
	int margin_y;	//���̶��߾�
	float chessSize;

	vector<vector<int>> chessMap;	//��ǰ��ֵ����ӷֲ����ݣ�0���գ� 1�����ӣ� -1������

	bool playerFlag;//���ڸ�˭���壬true:�����ߣ�false:������
};

