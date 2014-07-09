#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <map>
#include "ResourceLoader.h"

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