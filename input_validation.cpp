/* ==================================================================================================================================
	FILE:		input_validation.cpp - The Game of Life
	DETAIL:		Validates all user input. Checks for errors, ranges, etc
	DATES:		Created - 9/4/2014		Last Edit - 9/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include <iostream>
#include <sstream>

int validate_int(std::string question) {
	while (1) {
		std::cout << question;
		std::string user_input;
		std::cin >> user_input;

		// Constructs a istringstream object ss
		std::istringstream ss(user_input);
		int user_choice;
		ss >> user_choice;

		if (user_choice <= 0 || !ss.eof()) {
			std::cout << std::endl << "-------------------------------------------------- Input Error" << std::endl;
			std::cout << "Please enter a valid real number. ";
			std::cout << std::endl << "--------------------------------------------------" << std::endl << std::endl;
			continue;
		}
		else {
			return user_choice;
		}
	}
}


int validate_int_rage(std::string question, int min_range, int max_range) {
	while (1) {
		int user_choice = validate_int(question);
		if (user_choice > max_range || user_choice < min_range) {
			std::cout << std::endl << "-------------------------------------------------- Input Error" << std::endl;
			std::cout << "Sorry, your choice is out of range.";
			std::cout << std::endl << "--------------------------------------------------" << std::endl << std::endl;
			continue;
		}
		return user_choice;
	}
}

std::string validate_string(std::string question)
{
	std::cout << question;
	int input_attempt = 0;

	// 20 error attempts
	while (input_attempt < 20) {
		// Get user string input
		if (input_attempt != 0) { 
			std::cout << std::endl << "-------------------------------------------------- Input Error" << std::endl;
			std::cout << "Invalid input, try again. "; 
			std::cout << std::endl << "--------------------------------------------------" << std::endl << std::endl;
		
			std::cout << question;
		}
		
		input_attempt++;
		
		std::string user_input;
		std::getline(std::cin, user_input); // get the entire line, including spaces
		
		bool input_reject = false; 

		// Step through each character in the string until we either hit
		// the end of the string, or a rejected a character
		
		// No space at begginning allowed
		if (isspace(user_input[0]) || user_input == "")
			continue;
		
		for (int i = 0; i < user_input.length() && !input_reject; i++) {
			// Accept alpha character
			if (isalpha(user_input[i]))
				continue;

			// Accept Space
			if (user_input[i] == ' ')
				continue;
			
			// Recject other input
			input_reject = true;
		}

		// If the input has been accepted, exit the while loop
		// otherwise, loop again
		if (!input_reject)
			return user_input;
	}

	// If too many error inputs detected
	return "- User input error -";
}

void flush_input(std::istream& in){
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	in.clear();
}

void wait_for_input(std::string prompt_q) {
	std::cout << prompt_q;
	std::cin.get();
}