#pragma once
#include<graphics.h>
#include<vector>
#include<math.h>
using namespace std;
//����λ��
struct ChessPos {
	int row;
	int col;
};

//��������
typedef enum {
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1,//����
	CHESS_NONE = 0//����
}chess_kind_t;

class Chess
{
public:
	Chess(int gradesize, int margin_x, int margin_y, int chess_size);
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);//�������
	void chessDown(ChessPos * pos, chess_kind_t kind);//����
	int getGradeSize();//��ȡ���̴�С
	bool checkOver();//�ж��Ƿ����
	int getChessData(ChessPos *pos);//��ȡָ��λ�õ�����
private:
	IMAGE m_chessBlackImg; //��������ͼƬ
	IMAGE m_chessWhiteImg; //��������ͼƬ
	int m_gradesize; //���̴�С
	int m_margin_x;//�������ұ߽��С
	int m_margin_y;//�������±߽��С
	int m_chess_size;//���Ӵ�С ֱ���뷽����һ��Ӧ��һ��
	vector<vector<int>> m_chess_map;//��������
	bool m_chees_kind; // true������
	void updateGameMap(ChessPos* pos);
};

