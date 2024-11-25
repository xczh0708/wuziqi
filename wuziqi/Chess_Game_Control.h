#pragma once
#include"Chess.h"
#include"Player.h"
#include"ZHGO.h"
#include <cstdlib> 
#include <ctime> 
#include<string>
class Chess_Game_Control
{
public:
	Chess_Game_Control(Player* player, ZHGO* AI, Chess* chess);
	void begin_game();//开始对局
	void displayMenu();
	std::string getChoiceName(int choice);
	std::string determineWinner(int playerChoice, int computerChoice);
private:
	Player* m_player;
	ZHGO* m_AI;
	Chess* m_chess;
	int m_determineWinner = 0;
};

