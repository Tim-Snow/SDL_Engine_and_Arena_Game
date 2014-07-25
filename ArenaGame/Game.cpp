#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);

	fontColour = { 0, 255, 255, 255 };
	font = loadFont("text.TTF", 64);
	resources[GAME_FONT] = gfx->createTextTexture("Hellooooo", font, fontColour);

	GameObject textObject{ 50, 50, 450, 100, false, true };
	textObject.addTextureToObject(resources[GAME_FONT]);
	gameObjects.push_back(textObject);
}

SDL_Texture * Game::getTexture(const char* p){
	SDL_Surface * surf = res->loadBMP(p);
	texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

TTF_Font * Game::loadFont(const char* p, int size){
	if (font == nullptr){
		font = TTF_OpenFont(p, size);
	}
	return font;
}


Game::~Game(){
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
}