#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <memory>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

struct Controller{
	SDL_GameController* controller;
	std::map<SDL_GameControllerButton, bool> buttons;

	Controller(){
		controller = nullptr;
	}
	void setController(SDL_GameController* c){
		controller = c;
	}
	Controller(SDL_GameController* gc){
		controller = gc;
	}
	void setButton(SDL_GameControllerButton but, bool b){
		buttons[but] = b;
	}
	bool getButton(SDL_GameControllerButton but){
		return buttons[but];
	}
};

class InputManager{
public:
	static std::shared_ptr<InputManager> instance(){
		static std::shared_ptr<InputManager> instance = std::shared_ptr<InputManager>(new InputManager());
		return instance;
	}

	void pollEvent();
	bool isPressed(SDL_Keycode);
	bool isControllerPressed(int id, SDL_GameControllerButton but);
	bool isControllerPressed(SDL_GameControllerButton but);
	bool isControllerHeld(int id, SDL_GameControllerButton but);
	bool isHeld(SDL_Keycode);
	bool isAnyKeyPressed();
	bool checkQuit();
	void quit(){ run = false; }

	~InputManager();
private:
	InputManager();

	SDL_GameController * gCont;
	SDL_Event event;
	std::map<int, bool> keysP;
	std::map<int, bool> keysH;

	std::map<int, Controller> controllers;
	bool run;
	bool anyKey;
};
#endif /* defined  (_INPUTMANAGER_H_) */