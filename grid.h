/* ==================================================================================================================================
	FILE:		grid.h - The Game of Life
	DETAIL:		
	DATES:		Created - 11/4/2014		Last Edit - 11/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef GRID_H
#define GRID_H

#include <assert.h> // for assert()

class cGrid
{
protected:
	int *arr_data_ptr;	   // Present State array Pointer
	int *next_st_arr_ptr;  // Next State array Pointer
	int neighbours;
	int total_cells_alive;
public:
	int total_cells;
	int grid_length;

	cGrid();
	cGrid(int in_grid_size);
	~cGrid();

	int& operator[](int arr_element);

	void set_grid_size(int rows, int cols);
	int get_total_cells();

	int get_neighbours(int current_cell, cGrid&);

	void apply_rules(int current_cell, cGrid& player, int cell_neighbours);

	void set_alive_cells(int alive);
	int get_total_alive();
};

#endif