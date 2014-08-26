#ifndef GAME_H_
#define GAME_H_

#include "../Engine/Core.h"
//#include "../Engine/StateManager.h"
#include "TitleState.h"
#include <vector>

class State;

class Game{
public:
	Core core;

	TitleState titleScreen;

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	
	SDL_Texture * getTexture(char* p);

	void handleEvent();
	void draw();
	void update(double);


	
	Game();
	~Game();
private:
	SDL_Texture * texture;
};
#endif /* defined  (_GAME_H_) */_