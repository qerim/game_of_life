/* ==================================================================================================================================
	FILE:		Life_Game.h - The Game of Life
	DETAIL:		
	DATES:		Created - 16/4/2014		Last Edit - 16/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "grid.h"
#include "player.h"

class Life  : public cGrid
{
private:
	// Who the game has ended for
	int game_ended[3]; // 0 = Both, 1 = Player 1, 2 Player 2
	int alive_p1[2];
	int alive_p2[2];
	// 0 = Player 1, 1 = Player 2
	int same_pattern[2];
public:
	Life();
	void boot_up();
	void initialize(cGrid&, cGrid&);
	void print(cGrid&, cGrid&, bool game_ended);
	void update(cGrid&, cGrid&);

	void check_game_end(cGrid&, cGrid&);

	void set_game_ended(int end_game);
	int get_game_ended(int end_game);

	bool game_finished(cGrid&, cGrid&, bool restart_game);

	void gotoxy(int eex, int eey);
};

#endif