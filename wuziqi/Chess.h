#pragma once
#include<graphics.h>
#include<vector>
#include<math.h>
using namespace std;
//落子位置
struct ChessPos {
	int row;
	int col;
};

//落子类型
typedef enum {
	CHESS_WHITE = -1,//白棋
	CHESS_BLACK = 1,//黑棋
	CHESS_NONE = 0//无棋
}chess_kind_t;

class Chess
{
public:
	Chess(int gradesize, int margin_x, int margin_y, int chess_size);
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);//点击棋盘
	void chessDown(ChessPos * pos, chess_kind_t kind);//落子
	int getGradeSize();//获取棋盘大小
	bool checkOver();//判断是否结束
	int getChessData(ChessPos *pos);//获取指定位置的类型
private:
	IMAGE m_chessBlackImg; //黑棋棋子图片
	IMAGE m_chessWhiteImg; //白棋棋子图片
	int m_gradesize; //棋盘大小
	int m_margin_x;//棋盘左右边界大小
	int m_margin_y;//棋盘上下边界大小
	int m_chess_size;//棋子大小 直径与方格宽度一致应该一致
	vector<vector<int>> m_chess_map;//储存数组
	bool m_chees_kind; // true黑子走
	void updateGameMap(ChessPos* pos);
};

