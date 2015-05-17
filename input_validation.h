/* ==================================================================================================================================
	FILE:		input_validation.h - The Game of Life
	DETAIL:		Validates all user input. Checks for errors, ranges, etc
	DATES:		Created - 9/4/2014		Last Edit - 9/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef INPUT_VALIDATE_H
#define INPUT_VALIDATE_H

#include <string>

int validate_int(std::string question);

int validate_int_rage(std::string question, int min_range, int max_range);

std::string validate_string(std::string question);


void flush_input(std::istream& in);
void wait_for_input(std::string prompt_q);

#endif