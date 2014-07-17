#ifndef SETTINGS_H_
#define SETTINGS_H_
#include "ResourceLoader.h"
#include <map>


class Settings{
public:
	map<string, string> settings;
	void updateSettings();
	void saveSettings();
private:
	string settingsString;
	ResourceLoader loader;
};
#endif /* defined  (_SETTINGS_H_) */