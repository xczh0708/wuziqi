#pragma once
#include"Chess.h"
#include<iostream>
class Player
{
public:
	void init(Chess* chess);
	void go();
	int get_chess_val();
private:
	chess_kind_t m_chess_val;
	Chess *m_chess;
};

