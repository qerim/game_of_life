/* ==================================================================================================================================
	FILE:		welcome.cpp - The Game of Life
	DETAIL:		Displays welcoming message along with rules of the game and Menus
	DATES:		Created - 7/4/2014		Last Edit - 22/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include <iostream>
#include <iomanip>      // std::setw // time
#include <windows.h>
#include <string>
#include "messages.h"
#include "file_handler.h"
#include "input_validation.h"
#include "grid.h"
#include "settings.h"

cSettings prog_setting;

// ===== SET Welcome Message =====
void cMessages::set_wel_message() {
	// Reading from file
	welcome_message = get_file("welcome_en.txt");

	// If language is to be editted
	// edit_file("welcome.txt");
}

// ===== GET Welcome Message =====
std::string cMessages::get_wel_message() {
	return welcome_message;
}


void gotoxy(int x, int y) {
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void static_header(int grid_x_size) {
	std::cout << std::endl;
	for (int i = 0; i < (grid_x_size * 1.8) - 6; i++) { std::cout << ":"; }
	std::cout << " The Game of Life - EE273 ";
	for (int i = 0; i < (grid_x_size * 1.8) - 6; i++) { std::cout << ":"; }
}

bool cMessages::display_menu() {
	system("CLS");

	gotoxy(10, 2); std::cout << "Display Menu :: Game of Life";

	gotoxy(10, 4); std::cout << "___________________________________________";
	gotoxy(10, 6); std::cout << "[1] START Game";
	gotoxy(10, 7); std::cout << "[2] View Highscore [Unavaliable]";
	gotoxy(10, 8); std::cout << "[3] Help";
	gotoxy(10, 9); std::cout << "[4] Settings";
	gotoxy(10, 10); std::cout << "[5] Exit";
	gotoxy(10, 12); std::cout << "___________________________________________";
	
	gotoxy(10, 14); int user_choice = validate_int_rage("Enter your Selection: ", 1, 5);

	switch (user_choice)
	{
	case 1:
		system("CLS");
		return true;
	case 2:
		system("CLS");
		return false;
	case 3:
		system("CLS");
		std::cout << welcome_message;
		flush_input(std::cin); wait_for_input(""); // Wait for input confirm
		return false;
	case 4:
		system("CLS");
		display_settings();
		return false;
	case 5:
		system("CLS");
		exit(0);
	default: 
		std::cout << "Unexpected Input Error.";
		exit(0);
	}
}

void cMessages::display_settings() {
	gotoxy(10, 2); std::cout << "Settings :: Game of Life";

	gotoxy(10, 4); std::cout << "___________________________________________";
	gotoxy(10, 6); std::cout << "[1] Change Master Password [Not yet avaliable] ";
	gotoxy(10, 7); std::cout << "[2] Change Language [Not yet avaliable]";
	gotoxy(10, 8); std::cout << "[3] Change Master Password [Not yet avaliable] ";
	gotoxy(10, 9); std::cout << "[4] Main Menu ";
	gotoxy(10, 10); std::cout << "[5] Exit";
	gotoxy(10, 12); std::cout << "___________________________________________";

	gotoxy(10, 14); int user_choice = validate_int_rage("Enter your Selection: ", 1, 5);

	switch (user_choice)
	{
	case 1:
		system("CLS");
		//return true;
	case 2:
		system("CLS");
		//return false;
	case 3:
		system("CLS");
		std::cout << welcome_message;
		flush_input(std::cin); wait_for_input(""); // Wait for input confirm
		//return false;
	case 4:
		system("CLS");
		break;
	case 5:
		system("CLS");
		exit(0);
	default:
		std::cout << "Unexpected Input Error.";
		exit(0);
	}
}

void cMessages::game_header(int grid_x_size, cPlayer& Player_1, cPlayer& Player_2, cGrid& grid_Player1, cGrid& grid_Player2, bool game_end) {
	static_header(grid_x_size);
	
	std::cout << std::endl << std::endl;
	gotoxy(grid_x_size * 0.6, 4); std::cout << Player_1.get_name() << std::endl;
	gotoxy(grid_x_size * 2.8, 4); std::cout << Player_2.get_name() << std::endl;

	gotoxy(grid_x_size * 0.6, 5); std::cout << "Alive: " << std::setw(3) << grid_Player1.get_total_alive() << std::endl;   // setw(3) solved CLR screen problem
	gotoxy(grid_x_size * 2.8, 5); std::cout << "Alive: " << std::setw(3) << grid_Player2.get_total_alive() << std::endl;

	gotoxy(grid_x_size * 0.6, 6); std::cout << "Generation: " << Player_1.get_generations() << std::endl;
	gotoxy(grid_x_size * 2.8, 6); std::cout << "Generation: " << Player_2.get_generations() << std::endl;

	std::cout << std::endl;
	for (int i = 0; i < (grid_x_size * 4) + 4; i++) { std::cout << "-"; }
	std::cout << std::endl << std::endl << std::endl;

	if (!game_end)
	{
		grid_Player1.set_alive_cells(0);
		grid_Player2.set_alive_cells(0);
	}
}

void cMessages::game_footer(int grid_x_size) {
	std::cout << std::endl << std::endl;
	for (int i = 0; i < (grid_x_size * 4) + 4; i++) { std::cout << "-"; }
	std::cout << std::endl << std::endl << std::endl;
	if (prog_setting.get_manual_anime()){
		std::cout << "\t HOLD [Enter] key to simulate." << std::endl;
	}

	std::cout << "\t Press [Escape] key to quit and go to the menu ";  // only show this if Auto mode, not being detected in manual
}

bool cMessages::game_results(int grid_x_size, cPlayer& Player_1, cPlayer& Player_2, cGrid& grid_Player1, cGrid& grid_Player2) {
	system("CLS");

	game_header(grid_x_size, Player_1, Player_2, grid_Player1, grid_Player2, true);

	//wait_for_input("Game finished. Press [ENTER] to view results...");

	std::cout << "      Winner: ";

	if (Player_1.get_generations() > Player_2.get_generations()) { std::cout << Player_1.get_name(); }
	else if (Player_1.get_generations() < Player_2.get_generations()) { std::cout << Player_2.get_name(); }
	else { std::cout << "Both players scored equally!"; }

	std::cout << std::endl << std::endl;
	for (int i = 0; i < (grid_x_size * 4) + 4; i++) { std::cout << "-"; }

	std::cout << std::endl << std::endl;
	std::cout << "      [1] Main Menu" << std::endl;
	std::cout << "      [2] Exit" << std::endl << std::endl;

	for (int i = 0; i < (grid_x_size * 4) + 4; i++) { std::cout << "-"; }
	std::cout << std::endl << std::endl;

	int user_choice = validate_int_rage("      Enter your Selection: ", 1, 2);

	if (user_choice == 1) { return true; }
	else { exit(0); }
}