/* ==================================================================================================================================
	FILE:		player.h - The Game of Life
	DETAIL:		
	DATES:		Created - 15/4/2014		Last Edit - 15/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class cPlayer
{
private:
	bool turn;
	std::string name;
	int score;
	int generations;
public:
	cPlayer();

	void set_name(std::string player_name);
	std::string get_name();

	void set_score(int player_score);
	int get_score();

	void incre_generations();
	int get_generations();
};

#endif
