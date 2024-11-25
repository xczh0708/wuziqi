#include "Player.h"

void Player::init(Chess * chess)
{
	m_chess = chess;
}

void Player::go(int x,int y)
{

}

void Player::setChessVal(chess_kind_t chess_val)
{
	m_chess_val = chess_val;
}


