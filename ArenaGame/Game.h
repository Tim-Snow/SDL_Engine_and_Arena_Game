#ifndef GAME_H_
#define GAME_H_

#include "../Engine/Core.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TitleState.h"
#include <vector>

class State;

class Game{
public:
	static Game* instance()
	{
		static Game *instance = new Game();
		return instance;
	}

	Core core = Core::instance();

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	
	SDL_Texture * getTextTexture(const char*, TTF_Font*, SDL_Color);
	SDL_Texture * getTexture(char* p);

	void handleEvent();
	void draw();
	void update(double);

	void pushState(State*);
	void popState();

	~Game();
private:
	Game();

	std::vector<State*> state;
	SDL_Texture * texture;
};
#endif /* defined  (_GAME_H_) */_