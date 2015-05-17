/* ==================================================================================================================================
	FILE:			file_handler.cpp - The Game of Life
	DETAIL:		Responsible for all reading, writing and editting of local files.
	DATES:		Created - 7/4/2014		Last Edit - 7/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include <iostream>  // cin, cout
#include <fstream>	 // Input-Output file handling
#include <string>
#include "md5_hash.h"

#include "file_handler.h"

std::string file_directory = "./Text_Files/";

std::string get_file(std::string file_name) {
	std::string file_text;
	std::string file_line;

	std::ifstream infile;
	infile.open(file_directory + file_name);

	if (!infile.is_open()) {
		std::cout << std::endl << "==================================================================" << std::endl;
		std::cout << "  " << "Error: " << std::endl;
		std::cout << "  " << "The file" << " [" << file_name << "] " << "could not be opened." << std::endl << std::endl;
		std::cout << "  " << "Check the filename is correct and ensure that the file present. ";
		std::cout << std::endl << "==================================================================" << std::endl;
	}
	else {
		while (std::getline(infile, file_line))
		{
			file_text += file_line + std::string(1, '\n'); 
			// keeps \n formatting, website: 
			// www.stackoverflow.com/questions/18802398/how-do-i-retain-a-files-formatting-when-passing-its-data-into-a-string
		}
	}

	infile.close();			//	Close file

	// MD5 Hash check
	// std::cout << "MD5 Hash of " << " [" << file_name << "] " << ": " << md5(file_text) << std::endl;

	return file_text;
}

void edit_file(std::string file_name) {
	file_name = file_directory + file_name;
	std::string program = "notepad.exe " + file_name;
	system(program.c_str());
}

void write_file(std::string file_name, std::string file_content) {
	file_name = file_directory + file_name;
	std::ofstream outFile;
	outFile.open(file_name);
	outFile << file_content;
	outFile.close();
}