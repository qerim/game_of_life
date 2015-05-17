/* ==================================================================================================================================
	FILE:		Life_Game.cpp - The Game of Life
	DETAIL:
	DATES:		Created - 16/4/2014		Last Edit - 22/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include <iostream>  // cin, cout
#include <conio.h>
#include <windows.h> //	Windows GUI program
#include <iomanip>      // std::setw // time
#include "input_validation.h"

#include "Life_Game.h"
#include "messages.h"
#include "settings.h"
#include "player.h"

// Keyboard Key codes defined
#define arrow_UP 72
#define arrow_DOWN 80
#define arrow_LEFT 75
#define arrow_RIGHT 77
#define ENTER 13
#define ESCAPE 27
#define SPACE 32

cMessages game_message;
cPlayer Player_1, Player_2;				// Player 1, 2
cSettings game_settings;

int p1_random_seed = 2;
int p2_random_seed = 2;

Life::Life() {
	int game_ended[3] = {0};

	// last time, now
	int alive_p1[2] = {0};
	int alive_p2[2] = {0};

	// 0 = Player 1, 1 = Player 2
	int same_pattern[2] = {0};
}


void Life::set_game_ended(int end_game) {
	game_ended[end_game] = 1;
}

int Life::get_game_ended(int end_game) {
	return game_ended[end_game];
}


void Life::boot_up() {
	bool start_game = false;
	int AI_player;

	//===== Display Welcome Message =====
	game_message.set_wel_message(); // Read from Text file and store
	std::cout << game_message.get_wel_message();

	flush_input(std::cin); // Wait for input confirm

	game_settings.ShowConsoleCursor(true);

	while (!start_game) // begin when ready
		start_game = game_message.display_menu();

	std::cout << std::endl;
	AI_player = validate_int_rage("      Play against Computer (1), or another Human(2): ", 1, 2);

	wait_for_input("");

	std::cout << std::endl;
	Player_1.set_name(validate_string("      Player 1 name: "));

	//std::cout << std::endl;
	//p1_random_seed = validate_int_rage("      Would you like Manual(1) or Automatic random(2) grid generated: ", 1, 2);

	if (AI_player == 2)
	{
		std::cout << std::endl;
		Player_2.set_name(validate_string("      Player 2 name: "));

		//std::cout << std::endl;
		//p2_random_seed = validate_int_rage("      Would you like Manual(1) or Automatic random(2) grid generated: ", 1, 2);
	}
	else
	{
		Player_2.set_name("Computer AI");
		p2_random_seed = 2;
	}

	game_settings.set_manual_anime(true);

}

/* Make GOTOXY function */
void Life::gotoxy(int eex, int eey) {
	COORD coord;
	coord.X = eex;
	coord.Y = eey;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int x, y, lastx, lasty;


void Life::initialize(cGrid& grid_Player1, cGrid& grid_Player2) {	

	// random seed
	srand(int(time(0)));

	int initial_alive=  0;

		// Fill the array Player1
		for (int i = 0; i < get_total_cells(); i++)
		{

			grid_Player1[i] = rand() % 2;;
			if (grid_Player1[i] == 1)
			{
				initial_alive++;

			}
		}





	grid_Player1.set_alive_cells(initial_alive);

	initial_alive = 0;  // reset for player 2

		// Fill the array Player1
		for (int i = 0; i < get_total_cells(); i++) {

			grid_Player2[i] = rand() % 2;;
			if (grid_Player2[i] == 1) {
				initial_alive++;

			}
		}

	grid_Player2.set_alive_cells(initial_alive);
}

void Life::print(cGrid& grid_Player1, cGrid& grid_Player2, bool game_ended) {
	// Don't increment Generations if game has ended for player
	if (!get_game_ended(1)) { Player_1.incre_generations(); }
	if (!get_game_ended(2)) { Player_2.incre_generations(); }

	game_message.game_header(grid_length, Player_1, Player_2, grid_Player1, grid_Player2, game_ended);
	// -------------------------------------------------------

	// Make grid look square
	int split_square = int(sqrt(get_total_cells()));

	// player 2 cycle
	int k = 0;

	// Print out all the numbers
	for (int j = 0; j < get_total_cells(); j++) {
		std::cout << std::setw(2);
		if (grid_Player1[j] == 1)
		{
			std::cout << "*";
		}
		else { std::cout << " "; }

		// Make grid look square
		if ((j + 1) % split_square == 0) {

			std::cout << " | ";

			for (int z = 0; z < split_square; z++)
			{
				std::cout << std::setw(2);
				if (grid_Player2[k] == 1)
				{
					std::cout << "*";
				}
				else { std::cout << " "; }
				k++;

				if ((z + 1) % split_square == 0) {
					continue;
				}

			}
			// Take new line
			std::cout << std::endl;
		}

	}

	// -------------------------------------------------------
	game_message.game_footer(grid_length);
	// -------------------------------------------------------
}

void Life::update(cGrid& grid_Player1, cGrid& grid_Player2) {
	check_game_end(grid_Player1, grid_Player2);

	for (int i = 0; i < get_total_cells(); i++)
	{
		int cell_neighbours = get_neighbours(i, grid_Player1);
		apply_rules(i, grid_Player1, cell_neighbours);

		cell_neighbours = get_neighbours(i, grid_Player2);
		apply_rules(i, grid_Player2, cell_neighbours);
	}

}


void Life::check_game_end(cGrid& grid_Player1, cGrid& grid_Player2) {
	//--------------------------------------------------------------------
	// CHECK, ALIVE
	alive_p1[0] = alive_p1[1];
	alive_p2[0] = alive_p2[1];

	alive_p1[1] = 0;
	alive_p2[1] = 0;

	for (int q = 0; q < grid_Player1.get_total_cells(); q++)
	{
		if (grid_Player1[q] == 1) { alive_p1[1]++; }
		if (grid_Player2[q] == 1) { alive_p2[1]++; }
	}

	if (alive_p1[1] == alive_p1[0]) { same_pattern[0]++; }

	if (alive_p2[1] == alive_p2[0]) { same_pattern[1]++; }

	if (same_pattern[0] > 12 && same_pattern[1] > 12) { set_game_ended(0); }

	if (same_pattern[0] > 12) { set_game_ended(1); }

	if (same_pattern[1] > 12) { set_game_ended(2); }
	//--------------------------------------------------------------------
}

bool Life::game_finished(cGrid& grid_Player1, cGrid& grid_Player2, bool restart_game) {
	restart_game = game_message.game_results(grid_length, Player_1, Player_2, grid_Player1, grid_Player2);

	return restart_game;
}
