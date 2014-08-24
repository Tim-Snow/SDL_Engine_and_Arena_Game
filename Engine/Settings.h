#ifndef SETTINGS_H_
#define SETTINGS_H_
#include "ResourceLoader.h"
#include <cstdio>
#include <map>
#include <vector>

struct Resolution{
	int width;
	int height;
	Resolution(int w, int h) : width(w), height(h){	}

	int getW(){ return width; }
	int getH(){ return height; }
};

class Settings{
public:
	static Settings& instance(){
		static Settings *instance = new Settings();
		return *instance;
	}
	
	std::string getSetting(std::string);
	void addResolution(int w, int h);
	void setSetting(std::string, std::string);
	void setSetting(std::string, int);
	void updateSettings();
	void saveSettings();
private:
	Settings(){  }

	std::vector<Resolution> resolutions;
	std::map<std::string, std::string> settings;

};
#endif /* defined  (_SETTINGS_H_) */