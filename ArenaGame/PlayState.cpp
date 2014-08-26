#include "PlayState.h"



PlayState::PlayState(){}

void PlayState::init(){}

void PlayState::handleEvent(){
}

void PlayState::draw(){
}

void PlayState::update(double d){
}

void PlayState::clean(){
}


PauseState::PauseState(){}

void PauseState::init(){
	pauseMessage = gfx->getTextTexture("PAUSED", gfx->getFont(), { 255, 255, 255, 255 });
}

void PauseState::handleEvent(){

}

void PauseState::draw(){
	gfx->draw(pauseMessage, { 0, 0, 100, 100 });
}

void PauseState::update(double d){
}

void PauseState::clean(){
	SDL_DestroyTexture(pauseMessage);
}