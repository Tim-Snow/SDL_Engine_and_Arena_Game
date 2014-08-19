#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(){}

void PlayState::init(){
}

void PlayState::handleEvent(Game* g){
	if (g->input->isPressed(SDLK_ESCAPE))
		g->pushState(&PauseState::instance());
}

void PlayState::draw(Game* g){
}

void PlayState::update(Game* g, double d){

}

void PlayState::clean(){
}


PauseState::PauseState(){}

void PauseState::init(){
}

void PauseState::handleEvent(Game* g){
	if (g->input->isPressed(SDLK_ESCAPE))
		g->popState();
}

void PauseState::draw(Game* g){
}

void PauseState::update(Game* g, double d){

}

void PauseState::clean(){
}