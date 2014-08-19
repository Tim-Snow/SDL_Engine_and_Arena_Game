#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
}

void Game::handleEvent(){
	state.back()->handleEvent(this);
}

void Game::update(double d){
	input->pollEvent();
	state.back()->update(this, d);
}

void Game::draw(){
		gfx->clearDisplay();
		state.back()->draw(this);
		gfx->updateDisplay();
}

SDL_Texture * Game::getTexture(char* p){
	SDL_Surface* s = res->loadImage(p);
	texture = gfx->makeTextureFromSurf(s);
	SDL_FreeSurface(s);
	return texture;
}

SDL_Texture * Game::getTextTexture(const char* p, TTF_Font* f, SDL_Color c){
	SDL_Surface * surf = TTF_RenderText_Blended(f, p, c);
	texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

void Game::pushState(State* s){
	state.push_back(s);
	state.back()->init();
}

void Game::popState(){
	state.back()->clean();
	state.pop_back();
}

Game::~Game(){
	while (!state.empty()){
		state.back()->clean();
		state.pop_back();
	}

	SDL_DestroyTexture(texture);
	core.exit();
}