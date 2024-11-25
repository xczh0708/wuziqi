#pragma once
#include "Chess.h"
class ZHGO
{
public:
	void init(Chess *chess);
	void go();
	void setChessVal(chess_kind_t chess_val);
private:
	chess_kind_t m_chess_val;
	Chess* m_chess;
	vector<vector<int>> m_score_map;
protected:
	void calculateScore();
};

