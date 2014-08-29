#include "InputManager.h"

InputManager::InputManager() : run(true), anyKey(false), controllerIndex(0), alreadyPressed(false){
	menuWait = 0;
	deadZone = 10000;
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	if (SDL_NumJoysticks() > 0) {
		for (controllerIndex = 0; controllerIndex < SDL_NumJoysticks(); controllerIndex++){
			gCont = SDL_GameControllerOpen(controllerIndex);
			if (gCont != nullptr){
				controllers[controllerIndex].setController(gCont);
				std::cout << "Controller detected: " << controllerIndex << std::endl;
			}
		}
	}
}

void InputManager::pollEvent(){
	while (SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_QUIT:
			run = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.repeat == 0){
				anyKey = true;
				keysP[event.key.keysym.sym] = true;
				break;
			}	else  {
				anyKey = false;
				keysH[event.key.keysym.sym] = true;
				keysP[event.key.keysym.sym] = false;
				break;
			}
		case SDL_KEYUP:
			anyKey = false;
			keysP[event.key.keysym.sym] = false;
			keysH[event.key.keysym.sym] = false;
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			controllers[event.cdevice.which].setButton((SDL_GameControllerButton)event.cbutton.button, true);
			anyKey = true;
			break;
		case SDL_CONTROLLERBUTTONUP:
			controllers[event.cdevice.which].setButton((SDL_GameControllerButton)event.cbutton.button, false);
			anyKey = false;
			break;
		case SDL_CONTROLLERDEVICEADDED:
			gCont = SDL_GameControllerOpen(controllerIndex);
			if (gCont != nullptr){
				controllers[controllerIndex].setController(gCont);
				std::cout << "Controller detected: " << controllerIndex << std::endl;
				controllerIndex++;
			}
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			SDL_GameControllerClose(controllers[event.cdevice.which].controller);
			std::cout << "Controller removed: " << event.cdevice.which << std::endl;
			break;
		default:
			break;
		}
	}
}

JoystickDirections InputManager::isLeftJoystickMoved(SDL_GameController* c){
	JoystickDirections j = J_NONE;
	if (menuWait == 0){
		if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX) > deadZone)){
			j = J_RIGHT;
			menuWait++;
		}
		if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX) < -deadZone)){
			j = J_LEFT;
			menuWait++;
		}
		if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY) > deadZone)){
			j = J_DOWN;
			menuWait++;
		}
		if ((SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY) < -deadZone)){
			j = J_UP;
			menuWait++;
		}
	}
	if (menuWait != 0){
		menuWait++;
		if (menuWait >= 25){
			menuWait = 0;
		}
	}

	return j;
}

JoystickDirections InputManager::isLeftJoystickMoved(int i){
	JoystickDirections j = J_NONE;
	if (menuWait == 0){
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
	if (menuWait != 0){
		menuWait++;
		if (menuWait >= 10){
			menuWait = 0;
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
	return controllers[id].getButton(but);
}

bool InputManager::isControllerPressed(int id, SDL_GameControllerButton but){
	if(controllers[id].getButton(but)){
		controllers[id].setButton(but, false);
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
		if (controllers[i].getButton(but)){
			controllers[i].setButton(but, false);
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
		SDL_GameControllerClose(controllers[i].controller);
	}
	SDL_GameControllerClose(gCont);
}