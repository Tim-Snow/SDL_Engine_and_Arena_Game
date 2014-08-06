#ifndef SETTINGS_H_
#define SETTINGS_H_
#include "ResourceLoader.h"
#include <map>


class Settings{
public:
	std::map<std::string, std::string> settings;
	void updateSettings();
	void saveSettings();
private:
	std::string settingsString;
	ResourceLoader loader;
};
#endif /* defined  (_SETTINGS_H_) */