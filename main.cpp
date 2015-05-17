/* ==================================================================================================================================
	FILE:		main.cpp - The Game of Life
	DETAIL:		Starting point
	DATES:		Created - 7/4/2014		Last Edit - 22/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include <iostream>  // cin, cout
#include <conio.h>
#include <windows.h> //	Windows GUI programming.

// --------------------------------
#include "messages.h"
#include "player.h"
#include "grid.h"
#include "file_handler.h"
#include "input_validation.h"
#include "Life_Game.h"
#include "settings.h"
// --------------------------------

// Keyboard Key codes defined
#define ESCAPE 27

// Console Window dimensions
#define cnsl_win_x 120
#define cnsl_win_y 50

#define min_grid_size 10
#define max_grid_size 29

#define ANIME_SPEED 1  //  1 = fast (hungry), 50 = slow (less cpu)

#undef max   // causes problem "cin.ignore(numeric_limits <streamsize> ::max(), '\n');"
// ----------------------------------------------------------

void SetWindow(int Width, int Height) {
	system("COLOR 71"); // Console Colour - Background, Text

	// 0: Black, 1: Blue, 2: Green, 3: Aqua, 4: Red, 5: Purple, 6: Yellow, 7: White, 8: Gray, 9: Light Blue
	// A: Light Green, B: Light Aqua, C: Light Red, D: Light Purple, E: Light Yellow, F: Bright White

	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

void clearscreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

int main() {
	while (1) {
		system("CLS");
		cSettings main_settings;
		Life configuration;
		
		SetWindow(cnsl_win_x, cnsl_win_y); // Initialize Console Window
		main_settings.ShowConsoleCursor(false); // Hide blinking cursor
				
		configuration.boot_up();	// Get Player Detail

		// Grid Size
		std::cout << std::endl;
		int grid_size = validate_int_rage("      Enter a grid size (" + std::to_string(min_grid_size) + " to " + std::to_string(max_grid_size) + "): ", min_grid_size, max_grid_size);
		configuration.set_grid_size(grid_size, grid_size);

		wait_for_input("");

		std::cout << std::endl;
		int auto_seed = validate_int_rage("      Automatic[1] or Manual[2] Animation: ", 1, 2);
		if (auto_seed == 1)
			main_settings.set_manual_anime(false);

		// Declare grid Players
		cGrid grid_Player1(configuration.get_total_cells());	// Grid Player 1
		cGrid grid_Player2(configuration.get_total_cells());	// Grid Player 2
		
		configuration.initialize(grid_Player1, grid_Player2);	// Initialize

		system("CLS");
		configuration.print(grid_Player1, grid_Player2, false);		// Print

		char key = ' ';

		if (main_settings.get_manual_anime()) {
			flush_input(std::cin); // Wait until ENTER pressed
		}

		bool restart_game = false;

		while (key != ESCAPE && !restart_game) {
			if (_kbhit()) key = _getch(); // _kbhit - Checks the console for keyboard input.

			if (main_settings.get_manual_anime()) {
				char k = _getch();
				if (k == ESCAPE){ break; }
			}

			if (!configuration.get_game_ended(0)) {
				clearscreen();
				configuration.update(grid_Player1, grid_Player2);		// Update
				configuration.print(grid_Player1, grid_Player2, configuration.get_game_ended(0));		// Print
				Sleep(ANIME_SPEED);   // don't use 100% cpu
			}
			else {
				restart_game = configuration.game_finished(grid_Player1, grid_Player2, restart_game);
			}
		}
	}
}