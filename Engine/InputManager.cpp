#include "InputManager.h"

InputManager::InputManager() : run(true), anyKey(false), alreadyPressed(false), menuWait(0), deadZone(10000){
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (controllerIndex = 0; controllerIndex < SDL_NumJoysticks(); controllerIndex++){
		addGameController(controllerIndex);
	}
}

void InputManager::addGameController(int id){
	for (int i = 0; i < controllers.size()+1; i++){	//scans through controller map size + 1, meaning if all slots are in use, it will create one
		if (controllers[i].inUse != true){	//finds first available slot to assign controller
			gCont = SDL_GameControllerOpen(id);
			if (gCont != nullptr){
				SDL_Joystick* joystick		= SDL_GameControllerGetJoystick(gCont);	//joystick used simply for id to talk with event.cdevice.which
				controllers[i].id			= SDL_JoystickInstanceID(joystick);
				controllers[i].inUse		= true;
				controllers[i].controller	= gCont;
				std::cout << "Controller detected: " << i << std::endl;
				break;	//if it has gotten this far, the controller has been added for the correct id, so stop the loop
	}	}	}	}

void InputManager::removeGameController(int id){
	for (int i = 0; i < controllers.size(); i++){
		if (controllers[i].id == id && controllers[i].inUse == true){
			gCont = controllers[i].controller;
			SDL_GameControllerClose(gCont);
			controllers[i].inUse = false;
			std::cout << "Controller removed: " << i << std::endl;
		}
	}
}

void InputManager::pollEvent(){
	while (SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_QUIT:
			run = false;
			break;
		case SDL_CONTROLLERDEVICEADDED:
			addGameController(event.cdevice.which);		
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			removeGameController(event.cdevice.which);
			break;
		case SDL_KEYDOWN:
			if (event.key.repeat == 0){
				anyKey = true;
				keysP[event.key.keysym.sym] = true;
				keysH[event.key.keysym.sym] = true;
				break;
			}	else  {
				anyKey = false;
				keysP[event.key.keysym.sym] = false;
				break;
			}
		case SDL_KEYUP:
			anyKey = false;
			keysP[event.key.keysym.sym] = false;
			keysH[event.key.keysym.sym] = false;
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			for (int i = 0; i < controllers.size(); ++i){
				if (controllers[i].id == event.cdevice.which){
					controllers[i].buttons[(SDL_GameControllerButton)event.cbutton.button] = true;
				}
			}
			anyKey = true;
			break;
		case SDL_CONTROLLERBUTTONUP:
			for (int i = 0; i < controllers.size(); ++i){
				if (controllers[i].id == event.cdevice.which){
					controllers[i].buttons[(SDL_GameControllerButton)event.cbutton.button] = false;
				}
			}
			anyKey = false;
			break;
		default:
			break;
		}
	}
}

JoystickDirections InputManager::isLeftJoystickMoved(SDL_GameController* c){
	JoystickDirections j = J_NONE;
	SDL_Joystick* joystick = SDL_GameControllerGetJoystick(c);
	for (int i = 0; i<numControllers(); ++i){
		if (controllers[i].id = SDL_JoystickInstanceID(joystick)){
			if (controllers[i].controllerMenuWait == 0){
				if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX) > deadZone)){
					j = J_RIGHT;
					controllers[i].controllerMenuWait++;
				}
				if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX) < -deadZone)){
					j = J_LEFT;
					controllers[i].controllerMenuWait++;
				}
				if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY) > deadZone)){
					j = J_DOWN;
					controllers[i].controllerMenuWait++;
				}
				if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY) < -deadZone)){
					j = J_UP;
					controllers[i].controllerMenuWait++;
				}
			}
			if (controllers[i].controllerMenuWait != 0){
				controllers[i].controllerMenuWait++;
				if (controllers[i].controllerMenuWait >= 10){
					controllers[i].controllerMenuWait = 0;
				}
			}
		}
	}
	return j;
}

JoystickDirections InputManager::isLeftJoystickMoved(int i){
	JoystickDirections j = J_NONE;
	if (controllers[i].controllerMenuWait == 0){
		if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTX) > deadZone)){
			j = J_RIGHT;
			++controllers[i].controllerMenuWait;
		}
		if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTX) < -deadZone)){
			j = J_LEFT;
			++controllers[i].controllerMenuWait;
		}
		if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTY) > deadZone)){
			j = J_DOWN;
			++controllers[i].controllerMenuWait;
		}
		if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTY) < -deadZone)){
			j = J_UP;
			++controllers[i].controllerMenuWait;
		}
	}
	if (controllers[i].controllerMenuWait != 0){
		++controllers[i].controllerMenuWait;
		if (controllers[i].controllerMenuWait >= 10){
			controllers[i].controllerMenuWait = 0;
		}
	}

	return j;
}

JoystickDirections InputManager::isAnyLeftJoystickMoved(){
	JoystickDirections j = J_NONE;
	if (menuWait == 0){
		for (Uint8 i = 0; i < controllers.size(); i++){
			if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTX) > deadZone)){
				j = J_RIGHT;
				menuWait++;
			}
			if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTX) < -deadZone)){
				j = J_LEFT;
				menuWait++;
			}
			if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTY) > deadZone)){
				j = J_DOWN;
				menuWait++;
			}
			if ((SDL_GameControllerGetAxis(controllers[i].controller, SDL_CONTROLLER_AXIS_LEFTY) < -deadZone)){
				j = J_UP;
				menuWait++;
			}
		}
	}
	if (menuWait != 0){
		menuWait++;
		if (menuWait >= 10){
			menuWait = 0;
		}
	}

	return j;
}

bool InputManager::isControllerHeld(int id, SDL_GameControllerButton but){
	return controllers[id].buttons[but];
}

bool InputManager::isControllerPressed(int id, SDL_GameControllerButton but){
	if (controllers[id].buttons[but]){
		controllers[id].buttons[but] = false;
		return true;
	}
	return false;
}

bool InputManager::isControllerPressed(SDL_GameController* id, SDL_GameControllerButton but){
	if (SDL_GameControllerGetButton(id, but) == 1 && (alreadyPressed == false)){
		alreadyPressed = true;
		return true;
	}
	if (SDL_GameControllerGetButton(id, but) == 0){
		alreadyPressed = false;
	}
	return false;
}

bool InputManager::isControllerPressed(SDL_GameControllerButton but){
	for (Uint8 i = 0; i < controllers.size(); i++){
		if (controllers[i].buttons[but]){
			controllers[i].buttons[but] = false;
			return true;
		}
	}
	return false;
}

bool InputManager::isAnyKeyPressed(){  	
	if (anyKey){
		anyKey = false;
		return true;
	}
	else return false;
}

bool InputManager::isPressed(SDL_Keycode k){
	if (keysP[k]){
		keysP[k] = false;
		return true;
	} else return false;
}

InputManager::~InputManager(){
	for (Uint8 i = 0; i < controllers.size(); i++){
		if (controllers[i].inUse){
			gCont = controllers[i].controller;
			SDL_GameControllerClose(gCont);
		}
	}
}