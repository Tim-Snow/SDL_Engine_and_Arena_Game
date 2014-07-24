#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);

	resources[0] = gfx->renderText("Hellooooo", "text.TTF", { 255, 255, 0, 255 }, 64);
	GameObject a{ 50, 50, 450, 100, true, true };
	a.addTextureToObject(resources[0]);
	gameObjects.push_back(a);
}

SDL_Texture * Game::getTexture(const char* p){
	SDL_Surface * surf = res->loadBMP(p);
	texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

Game::~Game(){
	SDL_DestroyTexture(texture);
}