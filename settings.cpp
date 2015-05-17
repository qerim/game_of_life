/* ==================================================================================================================================
	FILE:		settings.cpp - The Game of Life
	DETAIL:		All game settings, passwords
	DATES:		Created - 7/4/2014		Last Edit - 22/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#include <iostream>  // cin, cout
#include <string>
#include <conio.h>
#include <windows.h> //	Windows GUI programming.

#include "settings.h"
#include "md5_hash.h"
#include "file_handler.h"

// Constructor
cSettings::cSettings(){
	secret_key = "ee273";
	manual_anime = true;
}

void cSettings::set_password(std::string password) {
	master_password = password;
}

std::string cSettings::get_password() {
	return master_password;
}

void cSettings::change_file_password(){
	// before changing password they have to know old one
	std::string new_password = master_password + secret_key;

	new_password = md5(new_password);

	std::cout << std::endl << "==================================================================" << std::endl;
	write_file("password.txt", new_password);
	std::cout << "Password changed successfully.";
	std::cout << std::endl << "==================================================================" << std::endl;
}

void cSettings::check_password() {
	std::string password = get_file("password.txt");
	password = password.substr(0, password.size() - 1); // remove last character from string, '\n'

	std::string user_password;

	std::cout << std::endl << "==================================================================" << std::endl;
	std::cout << "A password is needed to alter settings.";
	std::cout << std::endl << "Enter Password: ";
	std::cin >> user_password;
	std::cout << "==================================================================" << std::endl;

	user_password = user_password + secret_key;

	if (md5(user_password) == password) {
		std::cout << std::endl << "Password entered correctly." << std::endl;
	}
	else {
		std::cout << std::endl << "Inccorect password entered." << std::endl;
	}
}


void cSettings::set_manual_anime(bool manual_step) {
	manual_anime = manual_step;
}


bool cSettings::get_manual_anime() {
	return manual_anime;
}

void cSettings::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}