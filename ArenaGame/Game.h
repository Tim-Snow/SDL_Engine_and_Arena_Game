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
	Core core;

	TitleState titleScreen;
	MenuState mainMenu;
	MenuState optionsMenu;
	PlayState playGame;
	PauseState pauseGame;

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	
	SDL_Rect setRectToMiddle(int size);
	SDL_Texture * getTextTexture(const char*, TTF_Font*, SDL_Color);
	SDL_Texture * getTexture(char* p);
	TTF_Font	* getFont();
	
	void handleEvent();
	void draw();
	void update(double);

	void pushState(State*);
	void popState();
	
	Game();
	~Game();
private:
	std::vector<State*> state;

	SDL_Texture * texture;
	TTF_Font	* font;
};
#endif /* defined  (_GAME_H_) */_