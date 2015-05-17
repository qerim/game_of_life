/* ==================================================================================================================================
	FILE:		file_handler.h - The Game of Life
	DETAIL:		Declares global functions for dealing with reading,writing and editting of files
	DATES:		Created - 7/4/2014		Last Edit - 7/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>

// Global Function
std::string get_file(std::string file_name);

void edit_file(std::string file_name);

void write_file(std::string file_name, std::string file_content);

#endif