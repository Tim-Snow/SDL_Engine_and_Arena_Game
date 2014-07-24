#ifndef GAME_H_
#define GAME_H_

#include "GameObject.h"
#include "../Engine/Core.h"
#include "../Engine/ResourceLoader.h"
#include <vector>
#include <array>

class Game{
public:
	Game();
	~Game();

	Core core;
	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ResourceLoader> res;

	std::array<SDL_Texture*, 10> resources;
	std::vector<GameObject> gameObjects;

	SDL_Texture * getTexture(const char* p);
private:
	SDL_Texture * texture;
protected:

};


#endif /* defined  (_GAME_H_) */_