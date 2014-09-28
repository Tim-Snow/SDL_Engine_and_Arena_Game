#include "InputManager.h"

InputManager::InputManager() : run(true), anyKey(false), alreadyPressed(false), menuWait(0), deadZone(10000){
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (controllerIndex = 0; controllerIndex < SDL_NumJoysticks(); ++controllerIndex){
		controllers[getAvailController()].addGameController(controllerIndex);
	}
	reload();
}

//Sets any disconnected controllers to -1, rechecks currently opened controllers incase joy id had changed
void InputManager::reload(){
	for (int j = 0; j < controllers.size(); j++){
		if (controllers[j].inUse){
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controllers[j].controller);
			controllers[j].joyId = SDL_JoystickInstanceID(joystick);

			if (controllers[j].joyId == -1){
				controllers[j].inUse = false;
			}
			std::cout << "Controller at: " << j << " joyId: " << controllers[j].joyId << " in use: " << controllers[j].inUse << std::endl;
}	}	}

void Controller::addGameController(int id){
	controller = SDL_GameControllerOpen(id);
	if (controller != nullptr){
		instanceID = id;
		inUse = true;
}	}

//Removes any controller with -1 joy id
void InputManager::removeGameController(){
	for (int i = 0; i < controllers.size(); i++){
		if (controllers[i].controller != nullptr && controllers[i].joyId == -1){
			SDL_GameControllerClose(controllers[i].controller);
		}
	}
}

//Find what mapped controller has the same joystick id
int InputManager::getIndex(SDL_JoystickID id){
	for (int i = 0; i < controllers.size(); i++){
		if (controllers[i].inUse && controllers[i].joyId == id){
			return i;
		}
	}
	return -1; //id of invalid joysticks
}

//Finds first entry in controller map that is empty, able to make the map 'grow'
int InputManager::getAvailController(){
	for (int i = 0; i < controllers.size() + 1; i++){
		if (!controllers[i].inUse){
			return i;
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
			controllers[getAvailController()].addGameController(event.cdevice.which);
			reload();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			reload();
			removeGameController();
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
			controllerIndex = getIndex(event.cbutton.which);
			controllers[controllerIndex].controllerAction(event.cbutton);
			anyKey = true;
			break;
		case SDL_CONTROLLERBUTTONUP:
			controllerIndex = getIndex(event.cbutton.which);
			controllers[controllerIndex].controllerAction(event.cbutton);
			anyKey = false;
			break;
		default:
			break;
		}
	}
}

void Controller::controllerAction(const SDL_ControllerButtonEvent e){
	buttons[(SDL_GameControllerButton)e.button] = e.state;
}

int InputManager::getControllerAxisValue(int id, SDL_GameControllerAxis a){
	return SDL_GameControllerGetAxis(controllers[id].controller, a);
}

JoystickDirections InputManager::isLeftJoystickMoved(SDL_GameController* c){
	JoystickDirections j = J_NONE;
	SDL_Joystick* joystick = SDL_GameControllerGetJoystick(c);

	for (int i = 0; i<controllers.size(); ++i){
		if (controllers[i].joyId = SDL_JoystickInstanceID(joystick)){
			if (controllers[i].controllerMenuWait != 0){
				controllers[i].controllerMenuWait++;
				if (controllers[i].controllerMenuWait >= 10){
					controllers[i].controllerMenuWait = 0;
				}
			}

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
		}
	}
	return j;
}

JoystickDirections InputManager::isLeftJoystickMoved(int i){
	JoystickDirections j = J_NONE;

	if (controllers[i].controllerMenuWait != 0){
		++controllers[i].controllerMenuWait;
		if (controllers[i].controllerMenuWait >= 10){
			controllers[i].controllerMenuWait = 0;
		}
	}

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

bool InputManager::isControllerPressed(SDL_GameControllerButton but, int id){
	if (id == -1){ //if the default parameter remains (no controller specified), check for all controllers
		for (Uint8 i = 0; i < controllers.size(); i++){
			if (isControllerPressed(but, i) && controllers[i].inUse){
				return true;
			}
		}
		return false;
	}

	else if (controllers[id].buttons[but]){
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

bool InputManager::isAnyKeyPressed(){  	
	if (anyKey){
		anyKey = false;
		return true;
	}
	return false;
}

bool InputManager::isPressed(SDL_Keycode k){
	if (keysP[k]){
		keysP[k] = false;
		return true;
	} 
	return false;
}

void Controller::closeController(){
	if (controller != nullptr)
		SDL_GameControllerClose(controller);
}

InputManager::~InputManager(){
	for (int i = 0; i < controllers.size(); i++){
		controllers[i].closeController();
	}
	controllers.clear();
}