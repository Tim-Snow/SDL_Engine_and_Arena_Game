#ifndef GAME_H_
#define GAME_H_

#include "../Engine/Core.h"
#include "TitleState.h"
#include <vector>

class State;

class Game{
public:
	Core core;

	TitleState titleScreen;
	MenuState backState;

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	
	SDL_Texture * getTexture(char* p);

	void handleEvent();
	void draw();
	void update(double);

	State * getState() { return state.back(); }
	void pushState(State*);
	void popState();
	
	Game();
	~Game();
private:
	std::vector<State*> state;

	SDL_Texture * texture;

};
#endif /* defined  (_GAME_H_) */_