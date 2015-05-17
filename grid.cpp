/* ==================================================================================================================================
	FILE:		grid.cpp - The Game of Life
	DETAIL:
	DATES:		Created - 18/4/2014		Last Edit - 18/4/2014
	DEVELOPER: QJ
================================================================================================================================== */
#include <iostream>  // cin, cout
#include "Life_Game.h"
#include <assert.h> // for assert()

cGrid::cGrid() {
	total_cells = 0;
	arr_data_ptr = 0;
	next_st_arr_ptr = 0;
	total_cells_alive = 0;
}

cGrid::cGrid(int in_grid_size) {
	arr_data_ptr = new int[in_grid_size];
	next_st_arr_ptr = new int[in_grid_size];
	total_cells = in_grid_size;
}

cGrid::~cGrid() {
	delete[] arr_data_ptr;
	delete[] next_st_arr_ptr;
}

// overload the [] operator so we can access the elements of the array. 
// We should bounds check the index to make sure it’s valid, which is best done using the assert() 
int& cGrid::operator[](int arr_element) {
	//std::cout << "qerim: " << arr_element << std::endl;
	assert(arr_element >= 0 && arr_element < total_cells);
	return arr_data_ptr[arr_element];
}

void cGrid::set_grid_size(int rows, int cols) { total_cells = rows*cols; grid_length = cols; }
int cGrid::get_total_cells() { return total_cells; }

void cGrid::set_alive_cells(int alive) { total_cells_alive = alive; };
int cGrid::get_total_alive() { return total_cells_alive; }

int cGrid::get_neighbours(int current_cell, cGrid& player) {
	int chk_UP = 1, chk_DOWN = 1, chk_LEFT = 1, chk_RIGHT = 1, chk_UP_LEFT = 1, chk_UP_RIGHT = 1, chk_DOWN_LEFT = 1, chk_DOWN_RIGHT = 1;

	int neighbour = 0;
	int neighbour_alive = 0;

	// --------------------------------------------------------------------------------------------
	// TOP Line
	if (current_cell <= (grid_length - 1)) { chk_UP = 0; chk_UP_LEFT = 0; chk_UP_RIGHT = 0; }

	// RIGHT Line
	if (current_cell >= grid_length - 1 && ((current_cell + 1) % grid_length == 0) && current_cell <= total_cells - 1) { chk_RIGHT = 0; chk_DOWN_RIGHT = 0; chk_UP_RIGHT = 0; }

	// BOTTOM Line
	if (current_cell >= (total_cells - grid_length) && current_cell <= (total_cells - 1)) { chk_DOWN = 0; chk_DOWN_RIGHT = 0; chk_DOWN_LEFT = 0; }

	// LEFT Line
	if (current_cell % grid_length == 0) { chk_LEFT = 0; chk_UP_LEFT = 0; chk_DOWN_LEFT = 0; }
	// --------------------------------------------------------------------------------------------


	// UP-LEFT CORNER CELL
	if (current_cell == 0) { chk_LEFT = 0; chk_DOWN_LEFT = 0; }

	// UP-RIGHT CORNER CELL
	if (current_cell == (grid_length - 1)) { chk_RIGHT = 0; chk_DOWN_RIGHT = 0; }

	// BOTTOM-LEFT CORNER CELL
	if (current_cell == (total_cells - grid_length)) { chk_LEFT = 0; chk_UP_LEFT = 0; }

	// BOTTOM-RIGHT CORNER CELL
	if (current_cell == (total_cells - 1)) { chk_DOWN = 0; chk_DOWN_LEFT = 0; }


	if (chk_UP) {
		neighbour = player[current_cell - grid_length];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_DOWN) {
		neighbour = player[current_cell + grid_length];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_LEFT) {
		neighbour = player[current_cell - 1];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_RIGHT) {
		neighbour = player[current_cell + 1];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_UP_LEFT) {
		neighbour = player[current_cell - grid_length - 1];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_UP_RIGHT) {
		neighbour = player[current_cell - grid_length + 1];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_DOWN_LEFT) {
		neighbour = player[current_cell + grid_length - 1];
		if (neighbour == 1){ neighbour_alive++; }
	}

	if (chk_DOWN_RIGHT) {
		neighbour = player[current_cell + grid_length + 1];
		if (neighbour == 1){ neighbour_alive++; }
	}

	return neighbour_alive;	
}

void cGrid::apply_rules(int current_cell, cGrid& player, int cell_neighbours) {	
	// RULES OF THE GAME  --------------------------------------
	if (player.arr_data_ptr[current_cell] == 1) {
		if (cell_neighbours < 2){ player.next_st_arr_ptr[current_cell] = 0; }
		if (cell_neighbours == 2 || cell_neighbours == 3){ player.next_st_arr_ptr[current_cell] = 1; player.total_cells_alive++; }
		if (cell_neighbours > 3){ player.next_st_arr_ptr[current_cell] = 0; }
	}
	else if (player.arr_data_ptr[current_cell] == 0) {
		if (cell_neighbours == 3){ player.next_st_arr_ptr[current_cell] = 1; player.total_cells_alive++; }
	}
	else {
		player.next_st_arr_ptr[current_cell] = 0;
	}
	// ----------------------------------------------------------

	// Present State array = Next State array
	if (current_cell == total_cells - 1) {
		for (int k = 0; k < total_cells; k++) {
			player.arr_data_ptr[k] = player.next_st_arr_ptr[k];
		}	
	}
}