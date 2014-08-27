#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	loadResources();
	StateManager::instance().setup(gfx, input);
	StateManager::instance().pushState(&titleScreen);
}

void Game::loadResources(){
	SDL_Surface * surf = nullptr;

	surf = ResourceLoader::loadImage("res/titleBackground.png");
	ResourceLoader::addResource("menuBG", gfx->makeTextureFromSurf(surf));

	surf = ResourceLoader::loadImage("res/titleBackground2.png");
	ResourceLoader::addResource("menuBG2", gfx->makeTextureFromSurf(surf));

	SDL_FreeSurface(surf);
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
	ResourceLoader::clean();
	SDL_DestroyTexture(texture);
	core.exit();
}