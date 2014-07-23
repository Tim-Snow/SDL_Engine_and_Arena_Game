#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

class InputManager{
public:
	InputManager();
	~InputManager();

	void pollEvent();
	bool isPressed(SDL_Keycode);
	bool checkQuit();
private:
	SDL_Event event;
	std::map<int, bool> keys;
	bool run;
};
#endif /* defined  (_INPUTMANAGER_H_) */