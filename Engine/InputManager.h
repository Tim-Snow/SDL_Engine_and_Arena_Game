#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

class InputManager{
public:

	void pollEvent();
	bool isPressed(SDL_Keycode);
	bool isHeld(SDL_Keycode);
	bool isAnyKeyPressed();
	bool checkQuit();

	InputManager();
	~InputManager();
private:
	SDL_Event event;
	std::map<int, bool> keysP;
	std::map<int, bool> keysH;
	bool run;
	bool anyKey;
};
#endif /* defined  (_INPUTMANAGER_H_) */