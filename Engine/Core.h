#ifndef CORE_H_
#define CORE_H_

#include "ResourceLoader.h"
#include "InputManager.h"
#include "Settings.h"

class Core{
public:
	bool initialize();
	bool isRunning();
	void setTitle(string s);

	void updateInput();
	void updateDisplay();
	bool checkInput(SDL_Keycode);

	void exit();
private:
	SDL_Window * window;
	SDL_Renderer * renderer;

	int width, height;
	string name;
	bool running;

	ResourceLoader resources;
	InputManager theInput;
	Settings gameSettings;
};

#endif /* defined  (_CORE_H_) */