#ifndef CORE_H_
#define CORE_H_

#include "../SDL2.0\include\SDL.h"
#include "ResourceLoader.h"
#include "InputManager.h"
#include "Settings.h"

class Core{
public:
	bool initialize();
	void setTitle(string s);
	void mainLoop();
private:
	int width, height;
	string name;
	bool running;

	ResourceLoader resources;
	InputManager input;
	Settings gameSettings;

	void getInput();
	void draw();
	void update();
};


#endif /* defined  (_CORE_H_) */