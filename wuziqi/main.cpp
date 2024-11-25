#include<iostream>
#include"Chess_Game_Control.h"
int main(void) {
	int gradszie;
	std::cout << "ÇëÊäÈëÆåÆ×´óÐ¡";
	std::cin >> gradszie;

	Player player;
	Chess chess(gradszie);
	ZHGO ai;
	Chess_Game_Control game(&player,&ai,&chess);
	game.begin_game();
	return 0;
}