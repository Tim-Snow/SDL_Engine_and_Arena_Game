#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	pushState(&titleScreen);
}

void Game::handleEvent(){
	input->pollEvent();
	state.back()->handleEvent(this);
}

void Game::update(double d){
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

void Game::pushState(State* s){
	state.push_back(s);
	handleEvent();
	state.back()->init(this);
}

void Game::popState(){
	if (!state.empty()){
		state.back()->clean();
		state.pop_back();
		handleEvent();
	}
}

Game::~Game(){
	while (!state.empty()){
		state.back()->clean();
		state.pop_back();
	}

	SDL_DestroyTexture(texture);
	core.exit();
}