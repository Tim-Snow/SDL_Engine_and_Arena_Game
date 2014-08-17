#ifndef GAME_H_
#define GAME_H_

#include "../Engine/Core.h"
#include "../Engine/ResourceLoader.h"
#include "MenuState.h"
#include <vector>

class State;

class Game{
public:
	static Game& instance()
	{
		static Game *instance = new Game();
		return *instance;
	}
	
	Core core = Core::instance();

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	
	SDL_Texture * getTexture(char* p);
	SDL_Texture * getTextTexture(const char*);
	SDL_Texture * getResource(int);

	void handleEvent();
	void draw();
	void update(double);
	~Game();
private:
	Game();
	std::vector<State*> state;
};

#endif /* defined  (_GAME_H_) */_