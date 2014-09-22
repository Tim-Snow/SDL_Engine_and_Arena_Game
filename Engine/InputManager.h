#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <map>
#include <memory>
#include <iostream>
#include "../SDL2.0\include\SDL.h"

enum JoystickDirections{ J_NONE, J_UP, J_DOWN, J_LEFT, J_RIGHT };

class Controller{
public:
	Controller() : inUse(false), joyId(-1), controller(nullptr), controllerMenuWait(0), alreadyPressed(false) {}
	bool					inUse;
	int						controllerMenuWait;
	SDL_JoystickID			joyId;				
	SDL_GameController *	controller;
	std::map<SDL_GameControllerButton, bool>	buttons;

	void controllerAction(const SDL_ControllerButtonEvent);
	void addGameController(int id);
	void closeController();
private:
	bool alreadyPressed;
	int	 instanceID;
};

class InputManager{
public:
	static std::shared_ptr<InputManager> instance(){
		static std::shared_ptr<InputManager> instance = std::shared_ptr<InputManager>(new InputManager());
		return instance;
	}

	void	pollEvent();
	void	quit()				{ run		= false; }
	void	setDeadzone(int i)	{ deadZone	= i;	 }
	int		getDeadzone()		{ return deadZone;	 }
	bool	checkQuit()			{ return run;		 }

	JoystickDirections isLeftJoystickMoved(SDL_GameController*);
	JoystickDirections isLeftJoystickMoved(int);
	JoystickDirections isAnyLeftJoystickMoved();
	
	bool	isControllerAvailble(int id){ 	return controllers[id].inUse;	}
	bool	isHeld(SDL_Keycode k)		{	return keysH[k];				}
	bool	isPressed(SDL_Keycode);
	bool	isAnyKeyPressed();
	bool	isControllerPressed(SDL_GameController*, SDL_GameControllerButton);
	bool	isControllerPressed(SDL_GameControllerButton, int = -1);
	bool	isControllerHeld(int, SDL_GameControllerButton);
	
	~InputManager();
private:
	InputManager();
	void	removeGameController();
	int		getIndex(SDL_JoystickID);
	int		getAvailController();
	void	reload();

	SDL_Event					event;
	std::map<int, bool>			keysP;
	std::map<int, bool>			keysH;
	std::map<int, Controller>	controllers;

	int		menuWait, deadZone, controllerIndex;
	bool	alreadyPressed, run, anyKey;
};
#endif /* defined  (_INPUTMANAGER_H_) */