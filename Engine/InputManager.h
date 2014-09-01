#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <memory>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

enum JoystickDirections{ J_UP, J_DOWN, J_LEFT, J_RIGHT, J_NONE };

struct Controller{
	SDL_GameController* controller;
	std::map<SDL_GameControllerButton, bool> buttons;

	Controller(){
		controller = nullptr;
	}
	void setController(SDL_GameController* c){
		controller = c;
	}
	SDL_GameController* getController(){
		if (controller != nullptr){
			return controller;
		}
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
	void	pollEvent();
	void	setDeadzone(int i)	{ deadZone	= i;	 }
	void	quit()				{ run		= false; }
	int		getDeadzone()		{ return deadZone;	 }
	bool	checkQuit()			{ return run;		 }
	bool isHeld(SDL_Keycode k)	{ return keysH[k];	 }

	SDL_GameController* getController(int id){
		if (id < controllers.size()){
			return controllers[id].getController();
		}
		else return nullptr;
	}
	JoystickDirections isLeftJoystickMoved(SDL_GameController*);
	JoystickDirections isLeftJoystickMoved(int);
	JoystickDirections isAnyLeftJoystickMoved();

	bool isControllerPressed(SDL_GameController*, SDL_GameControllerButton);
	bool isControllerPressed(int, SDL_GameControllerButton);
	bool isControllerPressed(SDL_GameControllerButton);
	bool isControllerHeld(int, SDL_GameControllerButton);
	bool isPressed(SDL_Keycode);
	bool isAnyKeyPressed();
	
	~InputManager();
private:
	InputManager();

	SDL_GameController *		gCont;
	SDL_Event					event;
	std::map<int, bool>			keysP;
	std::map<int, bool>			keysH;
	std::map<int, Controller>	controllers;

	int menuWait;
	int deadZone;
	int controllerIndex;
	bool alreadyPressed;
	bool run;
	bool anyKey;
};
#endif /* defined  (_INPUTMANAGER_H_) */