#include "Game.h"

Game::Game(){
	gfx = core.gfxEng;
	input = core.theInput;

	resources[0] = getTexture("test.bmp");
	GameObject a{ 50, 50, 100, 100, true, true };
	a.addTextureToObject(resources[0]);

	gameObjects.push_back(a);
}

SDL_Texture * Game::getTexture(const char* p){
	SDL_Surface * surf = res->loadBMP(p);
	SDL_Texture * texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

Game::~Game(){

}