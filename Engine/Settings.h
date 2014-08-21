#ifndef SETTINGS_H_
#define SETTINGS_H_
#include "ResourceLoader.h"
#include <cstdio>
#include <map>

class Settings{
public:
	static Settings& instance(){
		static Settings *instance = new Settings();
		return *instance;
	}
	
	std::string getSetting(std::string);
	void setSetting(std::string, std::string);
	void setSetting(std::string, int);
	void updateSettings();
	void saveSettings();
private:
	Settings(){  }
	std::map<std::string, std::string> settings;
	ResourceLoader loader;
};
#endif /* defined  (_SETTINGS_H_) */