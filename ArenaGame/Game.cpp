#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	StateManager::instance().setup(gfx, input);
	StateManager::instance().pushState(&titleScreen);
}

void Game::handleEvent(){
	input->pollEvent();
	StateManager::instance().getState()->handleEvent();
}

void Game::update(double d){
	StateManager::instance().getState()->update(d);
}

void Game::draw(){
		gfx->clearDisplay();

		StateManager::instance().getState()->draw();
		gfx->updateDisplay();
}


Game::~Game(){
	StateManager::instance().clean();
	SDL_DestroyTexture(texture);
	core.exit();
}