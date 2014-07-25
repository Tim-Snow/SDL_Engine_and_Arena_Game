#ifndef GAME_H_
#define GAME_H_

#include "GameObject.h"
#include "../Engine/Core.h"
#include "../Engine/ResourceLoader.h"
#include "../Engine/MenuSystem.h"
#include <vector>
#include <array>

const int GAME_FONT = 0;

class Game{
public:
	Game();
	~Game();

	Core core;
	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;
	std::vector<GameObject> gameObjects;

	SDL_Texture * getTexture(const char* p);
	TTF_Font * loadFont(const char* p, int size);
private:
	std::array<SDL_Texture*, 10> resources;
	SDL_Texture * texture;
	TTF_Font * font;

	SDL_Colour fontColour;
protected:

};

#endif /* defined  (_GAME_H_) */_