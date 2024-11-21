#include "Player.h"

void Player::init(Chess * chess)
{
	m_chess = chess;
}

void Player::go()
{
	MOUSEMSG msg;
	ChessPos pos;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && m_chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	std::cout << pos.col << pos.row;
	//m_chess->chessDown(&pos,CHESS_BLACK);
}

int Player::get_chess_val()
{
	return 0;
}
