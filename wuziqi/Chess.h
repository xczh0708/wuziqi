#pragma once
#include<graphics.h>
#include<vector>
#include<math.h>
#include<iostream>
using namespace std;
//��������
typedef enum {
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1,//����
	CHESS_NONE = 0//����
}chess_kind_t;

class Chess
{
public:
	void init();
	Chess(int gradsize);
	void drawBoard();
	bool checkOver();//�ж��Ƿ����
	int getChessData(int x,int y);//��ȡָ��λ�õ�����
private:
	vector<vector<chess_kind_t>> m_chess_map;//��������
	bool m_chees_kind; // true������
	void updateGameMap(int x, int y);
	int m_gradSize;
};

