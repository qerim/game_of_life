/* ==================================================================================================================================
	FILE:		settings.h - The Game of Life
	DETAIL:		All game settings, passwords
	DATES:		Created - 7/4/2014		Last Edit - 7/4/2014
	DEVELOPER: QJ
================================================================================================================================== */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class cSettings
{
private:
	std::string master_password;
	std::string secret_key;

	bool manual_anime; // Animations manual/automatic
public:
	cSettings();
	void set_password(std::string password);
	std::string get_password();
	void change_file_password();
	void check_password();

	void set_manual_anime(bool manual_step);
	bool get_manual_anime();

	void ShowConsoleCursor(bool showFlag);
};

#endif