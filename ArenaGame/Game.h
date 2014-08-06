#ifndef GAME_H_
#define GAME_H_

#include "GameObject.h"
#include "../Engine/Core.h"
#include "../Engine/ResourceLoader.h"
#include <vector>
#include <array>

enum GAME_STATE { PLAY, PAUSE, TITLE_SCREEN, MAIN_MENU, CHAR_SELECT, OPTIONS_MENU };

const int MENU_BG = 0;

class Game{
public:
	Game();
	~Game();

	Core core;

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	
	SDL_Texture * getTexture(char* p);
	SDL_Texture * getTextTexture(const char*);
	SDL_Texture * getResource(int);
	void draw();
	void update(double);

private:
	std::vector<GAME_STATE> state;
	std::vector<GameObject> gameObjects;
	std::array<SDL_Texture*, 10> resources;
	SDL_Texture * texture;
	SDL_Colour fontColour;
	TTF_Font * font;

	void checkInputs();
	void loadResources();

	int menuWait;
protected:

};

#endif /* defined  (_GAME_H_) */_