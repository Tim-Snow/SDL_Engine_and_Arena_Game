#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(){}

void PlayState::init(Game* g){
	
}

void PlayState::handleEvent(Game* g){
	if (g->input->isPressed(SDLK_ESCAPE))
		g->pushState(&g->pauseGame);
}

void PlayState::draw(Game* g){
}

void PlayState::update(Game* g, double d){
}

void PlayState::clean(){
}


PauseState::PauseState(){}

void PauseState::init(Game* g){
	pauseMessage = g->getTextTexture("PAUSED", g->getFont(), { 255, 255, 255, 255 });
}

void PauseState::handleEvent(Game* g){
	if (g->input->isPressed(SDLK_ESCAPE))
		g->popState();
}

void PauseState::draw(Game* g){
	g->gfx->draw(pauseMessage, { 0, 0, 100, 100 });
}

void PauseState::update(Game* g, double d){
	std::cout << "Paused" << std::endl;
}

void PauseState::clean(){
}