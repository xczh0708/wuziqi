#include "Chess_Game_Control.h"

Chess_Game_Control::Chess_Game_Control(Player * player, ZHGO * AI, Chess * chess)
{
	this->m_player = player;
	this->m_AI = AI;
	this->m_chess = chess;
	player->init(chess);
}

void Chess_Game_Control::begin_game()
{
	m_chess->init();
	while (1) {
		m_player->go();
		if (m_chess->checkOver()) {
			m_chess->init();
			continue;
		}
		m_AI->go();
		if (m_chess->checkOver()) {
			m_chess->init();
			continue;
		}
	}
}
