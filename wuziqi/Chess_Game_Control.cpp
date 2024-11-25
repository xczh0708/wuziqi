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
	// ��ʾ�˵�����ȡ���ѡ��
	do{
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		int playerChoice;
		displayMenu();
		std::cin >> playerChoice;

		if (playerChoice < 1 || playerChoice > 3) {
			std::cout << "��Ч���룬��ѡ�� 1-3��" << std::endl;
			continue;
		}

		// �������ѡ��
		int computerChoice = std::rand() % 3 + 1;

		// ��ʾ˫��ѡ��
		std::cout << "��ѡ����: " << getChoiceName(playerChoice) << std::endl;
		std::cout << "����ѡ����: " << getChoiceName(computerChoice) << std::endl;

		// �ж�ʤ��
		std::cout << determineWinner(playerChoice, computerChoice) << std::endl;
	} while (m_determineWinner == 0);
	//-------------------------------------------------��ʼ��Ϸ------------------------------------------------------------------
	std::cout << "���������ʼ��Ϸ" << std::endl;
	std::cin.ignore();  // ������뻺����
	std::cin.get();     // �ȴ��û�����
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
	std::cout << "==== ��ȭ��Ϸ�����Ⱥ���====\n";
	std::cout << "1. ʯͷ\n";
	std::cout << "2. ����\n";
	std::cout << "3. ��\n";
	std::cout << "���������ѡ�� (1-3): ";
}

std::string Chess_Game_Control::getChoiceName(int choice)
{
	switch (choice) {
	case 1: return "ʯͷ";
	case 2: return "����";
	case 3: return "��";
	default: return "δ֪";
	}
}

std::string Chess_Game_Control::determineWinner(int playerChoice, int computerChoice)
{
	if (playerChoice == computerChoice) {
		return "ƽ�֣�";
	}

	if ((playerChoice == 1 && computerChoice == 2) || 
		(playerChoice == 2 && computerChoice == 3) || 
		(playerChoice == 3 && computerChoice == 1)) { 
		m_determineWinner = 1;
		m_player->setChessVal(CHESS_BLACK);
		m_AI->setChessVal(CHESS_WHITE);
		return "��Ӯ�ˣ���ִ����";
	}
	m_determineWinner = -1;
	m_player->setChessVal(CHESS_WHITE);
	m_AI->setChessVal(CHESS_BLACK);
	return "�����ˣ���ִ����";
}
