#include "InputManager.h"

InputManager::InputManager() : run(true){}

void InputManager::pollEvent(){
	while (SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				keys[event.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				keys[event.key.keysym.sym] = false;
				break;
			default:
				break;
		}
	}
}

bool InputManager::isPressed(SDL_Keycode k){  return keys[k];  }
bool InputManager::checkQuit(){  return run;  }

InputManager::~InputManager(){}