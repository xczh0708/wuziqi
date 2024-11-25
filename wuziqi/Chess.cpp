#include "Chess.h"
void Chess::init()
{
	for (int i = 0; i < m_gradSize; ++i) {
		vector<chess_kind_t> map;
		for (int j = 0; j < m_gradSize; ++j) {
			map.push_back(CHESS_NONE);
		}
		m_chess_map.push_back(map);
	}
}
Chess::Chess(int gradsize)
{
	m_gradSize = gradsize;
}

void Chess::drawBoard()
{
	system("cls");
	std::cout << "   ";
	for (int i = 0; i < m_gradSize; ++i) {
		std::cout << (i < 10 ? " " : "") << i << " ";
	}
	std::cout << std::endl;
	// 绘制行
	for (int i = 0; i < m_gradSize; ++i) {
		// 绘制行号
		std::cout << (i < 10 ? " " : "") << i << " ";

		// 绘制行内容
		for (int j = 0; j < m_gradSize; ++j) {
			if (m_chess_map[i][j] == CHESS_WHITE ) {
				std::cout << " " << "o" << " ";
			}
			if (m_chess_map[i][j] == CHESS_BLACK) {
				std::cout << " " << "*" << " ";
			}
			if (m_chess_map[i][j] == CHESS_NONE) {
				std::cout << " " << " " << " ";
			}
		}
		std::cout << std::endl;
	}
}




bool Chess::checkOver()
{
	return false;
}

int Chess::getChessData(int x, int y)
{
	return 0;
}

void Chess::updateGameMap(int x, int y)
{
	m_chess_map[x][y] = m_chees_kind ? CHESS_BLACK : CHESS_WHITE;

}
