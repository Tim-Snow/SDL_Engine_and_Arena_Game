#include "Settings.h"

//Reads game settings from ini file
void Settings::updateSettings(){
	fstream fileStream("settings.ini", ios::in);

	if (!fileStream.is_open()) {
		cout << "Settings.ini could not be opened" << endl;
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);

		int seperator = line.find("=");
		string tempKey = line.substr(0, seperator);
		string tempValue = line.substr(seperator + 1, line.length());

		settings[tempKey] = tempValue;
		cout << settings[tempKey] << tempKey << endl;
	}
	fileStream.close();
}

//Saves settings when modified or game closes
void Settings::saveSettings(){
	ofstream fileStream("settings.ini", ios::out);

	if (!fileStream.is_open()){
		cout << "Settings could not be saved" << endl;
	}

	for (auto x : settings){
		fileStream << "screenWidth=" << settings["screenWidth"] << endl;
		fileStream << "screenHeight=" << settings["screenHeight"] << endl;
		//needs to clear file before saving
	}
	fileStream.close();
}