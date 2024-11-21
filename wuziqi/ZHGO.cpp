#include "ZHGO.h"

void ZHGO::init(Chess * chess)
{
	m_chess = chess;
	for (int i = 0; i < chess->getGradeSize(); i++) {
		vector<int> row;
		for (int j = 0; j < chess->getGradeSize(); ++j) {
			row.push_back(0);
		}
		this->m_score_map.push_back(row);
	}
}

void ZHGO::go()
{
	ChessPos pos = think();
	Sleep(1000);
	m_chess->chessDown(&pos, CHESS_WHITE);
}

int ZHGO::get_chess_val()
{
	return 0;
}

void ZHGO::calculateScore()
{
}

ChessPos ZHGO::think()
{
	return ChessPos();
}
