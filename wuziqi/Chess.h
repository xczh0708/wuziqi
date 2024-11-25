#pragma once
#include<graphics.h>
#include<vector>
#include<math.h>
#include<iostream>
using namespace std;
//落子类型
typedef enum {
	CHESS_WHITE = -1,//白棋
	CHESS_BLACK = 1,//黑棋
	CHESS_NONE = 0//无棋
}chess_kind_t;

class Chess
{
public:
	void init();
	Chess(int gradsize);
	void drawBoard();
	bool checkOver();//判断是否结束
	int getChessData(int x,int y);//获取指定位置的类型
private:
	vector<vector<chess_kind_t>> m_chess_map;//储存数组
	bool m_chees_kind; // true黑子走
	void updateGameMap(int x, int y);
	int m_gradSize;
};

