#pragma once
#include"Chess.h"
#include"Player.h"
#include"ZHGO.h"
class Chess_Game_Control
{
public:
	Chess_Game_Control(Player* player, ZHGO* AI, Chess* chess);
	void begin_game();//开始对局
private:
	Player* m_player;
	ZHGO* m_AI;
	Chess* m_chess;
};

