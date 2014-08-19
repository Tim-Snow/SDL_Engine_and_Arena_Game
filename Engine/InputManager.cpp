#include "InputManager.h"

InputManager::InputManager() : run(true){}

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
		default:
			break;
		}
	}
}

bool InputManager::isAnyKeyPressed(){  	return anyKey;  }
bool InputManager::isHeld(SDL_Keycode k){  return keysH[k];  }
bool InputManager::isPressed(SDL_Keycode k){
	if (keysP[k]){
		keysP[k] = false;
		return true;
	} else return false;
}
bool InputManager::checkQuit(){  return run;  }

InputManager::~InputManager(){}