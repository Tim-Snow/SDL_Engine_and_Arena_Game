#include "Settings.h"

//Reads game settings from ini file
void Settings::updateSettings(){
	std::fstream fileStream("settings.ini", std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Settings.ini could not be opened" << std::endl;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);

		int seperator = line.find("=");
		std::string tempKey = line.substr(0, seperator);
		std::string tempValue = line.substr(seperator + 1, line.length());

		settings[tempKey] = tempValue;
		std::cout << settings[tempKey] << tempKey << std::endl;
	}
	fileStream.close();
}

//Saves settings when modified or game closes
void Settings::saveSettings(){
	std::ofstream fileStream("settings.ini", std::ios::out);

	if (!fileStream.is_open()){
		std::cout << "Settings could not be saved" << std::endl;
	}

	for (auto x : settings){
		fileStream << "screenWidth=" << settings["screenWidth"] << std::endl;
		fileStream << "screenHeight=" << settings["screenHeight"] << std::endl;
		//needs to clear file before saving
	}
	fileStream.close();
}