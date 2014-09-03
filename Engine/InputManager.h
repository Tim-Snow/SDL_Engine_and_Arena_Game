#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <memory>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

enum JoystickDirections{ J_UP, J_DOWN, J_LEFT, J_RIGHT, J_NONE };

struct Controller{
	bool inUse;
	int  id;
	int  controllerMenuWait;
	
	SDL_GameController	*	controller;
	std::map<SDL_GameControllerButton, bool> buttons;

	Controller() : controllerMenuWait(0), inUse(false), controller(nullptr){}
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

	int numControllers(){
		int j = 0;
		for (int i = 0; i < controllers.size(); ++i){
			if (controllers[i].inUse == true){
				j++;
		}	}
		return j; 
	}

	Controller getController(int i){ return controllers[i]; }

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
	void addGameController(int id);
	void removeGameController(int id);
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