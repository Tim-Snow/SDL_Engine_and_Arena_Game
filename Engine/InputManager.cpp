#include "InputManager.h"

InputManager::InputManager() : run(true), anyKey(false){

	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	if (SDL_NumJoysticks() > 0) {
		for (int i = 0; i < SDL_NumJoysticks(); i++){	
			gCont = SDL_GameControllerOpen(i);
			if (gCont != nullptr){
				controllers[i].setController(gCont);
				std::cout << "Controller detected: " << i << std::endl;
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
			controllers[event.cbutton.which].setButton((SDL_GameControllerButton)event.cbutton.button, true);
			anyKey = true;
			std::cout << "Controller ID: " << event.cbutton.which << " Button:  " << SDL_GameControllerGetStringForButton((SDL_GameControllerButton)event.cbutton.button) << std::endl;
			break;
		case SDL_CONTROLLERBUTTONUP:
			anyKey = false;
			break;
		case SDL_CONTROLLERAXISMOTION:
			break;
		default:
			break;
		}
	}
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

bool InputManager::isControllerPressed(SDL_GameControllerButton but){
	for (int i = 0; i < controllers.size(); i++){
		if (controllers[i].getButton(but)){
			controllers[i].setButton(but, false);
			return true;
		}
	}
	return false;
}

bool InputManager::isHeld(SDL_Keycode k){  return keysH[k];  }

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

bool InputManager::checkQuit(){  return run;  }
InputManager::~InputManager(){
	for (int i = 0; i < controllers.size(); i++){
		SDL_GameControllerClose(controllers[i].controller);
	}
	SDL_GameControllerClose(gCont);
}