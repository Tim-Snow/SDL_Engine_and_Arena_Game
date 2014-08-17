#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	state.push_back(&MenuState::instance());
}

void Game::handleEvent(){
	state.back()->handleEvent(this);
}

void Game::update(double d){
	state.back()->update(this);
}

void Game::draw(){
		gfx->clearDisplay();
		state.back()->draw(this);
		gfx->updateDisplay();
}

Game::~Game(){
	core.exit();
}