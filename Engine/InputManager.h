#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <memory>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

class InputManager{
public:
	static std::shared_ptr<InputManager> instance(){
		static std::shared_ptr<InputManager> instance = std::shared_ptr<InputManager>(new InputManager());;
		return instance;
	}

	void pollEvent();
	bool isPressed(SDL_Keycode);
	bool isHeld(SDL_Keycode);
	bool isAnyKeyPressed();
	bool checkQuit();
	void quit(){ run = false; }

	~InputManager();
private:
	InputManager();
	SDL_Event event;
	std::map<int, bool> keysP;
	std::map<int, bool> keysH;
	bool run;
	bool anyKey;
};
#endif /* defined  (_INPUTMANAGER_H_) */