#include "Settings.h"

void Settings::setSetting(std::string id, std::string value){
	settings[id] = value;
}

void Settings::setSetting(std::string id, int value){
	settings[id] = std::to_string(value);
}

std::string Settings::getSetting(std::string id){
	return settings.at(id);
}

//Reads game settings from ini file
void Settings::updateSettings(){
	std::ifstream fileStream("settings.ini", std::ifstream::in);

	if (!fileStream.is_open()) {
		std::cout << "Settings.ini could not be opened" << std::endl;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		if (line != ""){
			int seperator = line.find("=");
			std::string tempKey = line.substr(0, seperator);
			std::string tempValue = line.substr(seperator + 1, line.length());

			settings[tempKey] = tempValue;
			std::cout << tempKey << ": " << settings[tempKey] << std::endl;
		}
	}
	fileStream.close();
}

void Settings::saveSettings(){
	remove("settings.ini");
	std::ofstream fileStream("settings.ini", std::ofstream::out);

	if (fileStream.is_open()){
		fileStream << "screenWidth=" << getSetting("screenWidth") << std::endl;
		fileStream << "screenHeight=" << getSetting("screenHeight") << std::endl;
		fileStream << "fullscreen=" << getSetting("fullscreen") << std::endl;

	}
	fileStream.close();
}