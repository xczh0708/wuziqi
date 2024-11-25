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
	// 显示菜单并获取玩家选择
	do{
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		int playerChoice;
		displayMenu();
		std::cin >> playerChoice;

		if (playerChoice < 1 || playerChoice > 3) {
			std::cout << "无效输入，请选择 1-3！" << std::endl;
			continue;
		}

		// 电脑随机选择
		int computerChoice = std::rand() % 3 + 1;

		// 显示双方选择
		std::cout << "你选择了: " << getChoiceName(playerChoice) << std::endl;
		std::cout << "电脑选择了: " << getChoiceName(computerChoice) << std::endl;

		// 判断胜负
		std::cout << determineWinner(playerChoice, computerChoice) << std::endl;
	} while (m_determineWinner == 0);
	//-------------------------------------------------开始游戏------------------------------------------------------------------
	std::cout << "按任意键开始游戏" << std::endl;
	std::cin.ignore();  // 清除输入缓冲区
	std::cin.get();     // 等待用户按键
	m_chess->init();
	while (1) {
		m_chess->drawBoard();
		int x, y;
		if (m_determineWinner == 1) {
			
			m_player->go(x,y);
		}
		if (m_determineWinner == -1) {

		}
	}
	
	
}

void Chess_Game_Control::displayMenu()
{
	std::cout << "==== 猜拳游戏决定先后手====\n";
	std::cout << "1. 石头\n";
	std::cout << "2. 剪刀\n";
	std::cout << "3. 布\n";
	std::cout << "请输入你的选择 (1-3): ";
}

std::string Chess_Game_Control::getChoiceName(int choice)
{
	switch (choice) {
	case 1: return "石头";
	case 2: return "剪刀";
	case 3: return "布";
	default: return "未知";
	}
}

std::string Chess_Game_Control::determineWinner(int playerChoice, int computerChoice)
{
	if (playerChoice == computerChoice) {
		return "平局！";
	}

	if ((playerChoice == 1 && computerChoice == 2) || 
		(playerChoice == 2 && computerChoice == 3) || 
		(playerChoice == 3 && computerChoice == 1)) { 
		m_determineWinner = 1;
		m_player->setChessVal(CHESS_BLACK);
		m_AI->setChessVal(CHESS_WHITE);
		return "你赢了！你执黑棋";
	}
	m_determineWinner = -1;
	m_player->setChessVal(CHESS_WHITE);
	m_AI->setChessVal(CHESS_BLACK);
	return "你输了！你执白棋";
}
