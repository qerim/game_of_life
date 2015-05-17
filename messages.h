/* ==================================================================================================================================
	FILE:		welcome.h - The Game of Life
	DETAIL:		Responsible for all reading, writing and editting of local files.
	DATES:		Created - 7/4/2014		Last Edit - 7/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef WELCOME_H
#define WELCOME_H

#include <string>

#include "player.h"
#include "grid.h"

class cMessages
{
private:
	std::string welcome_message;
public:
	void set_wel_message();						// ===== SET Welcome Message =====
	std::string get_wel_message();		// ===== GET Welcome Message =====
	
	bool display_menu();
	void display_settings();

	void game_header(int grid_x_size, cPlayer&, cPlayer&, cGrid&, cGrid&, bool game_end);
	void game_footer(int grid_x_size);
	bool game_results(int grid_x_size, cPlayer&, cPlayer&, cGrid&, cGrid&);
};

#endif