/* ==================================================================================================================================
	FILE:		player.cpp - The Game of Life
	DETAIL:
	DATES:		Created - 15/4/2014		Last Edit - 15/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include "player.h"
#include <string>


cPlayer::cPlayer() {
	turn = false;
	generations = -1; // -1 because print increments first thing
}

void cPlayer::set_name(std::string player_name) {
	name = player_name;
	generations = -1;
}

std::string cPlayer::get_name() {
	return name;
}

void cPlayer::set_score(int player_highscore) {
	score = player_highscore;

	// Encrypt highscore in file
}

int cPlayer::get_score() {
	// READ md5 TEXTFILE
	return score;
}


void cPlayer::incre_generations() {
	generations ++;
}

int cPlayer::get_generations() {
	return generations;
}