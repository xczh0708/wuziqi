#include<iostream>
#include"Chess_Game_Control.h"

int main(void) {
	Player player;
	Chess chess(20,50,50,45);
	ZHGO ai;
	Chess_Game_Control game(&player,&ai,&chess);
	game.begin_game();
	return 0;
}