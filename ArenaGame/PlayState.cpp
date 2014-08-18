#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(){}

void PlayState::init(){
}

void PlayState::handleEvent(Game* g){
	g->input->pollEvent();
}

void PlayState::draw(Game* g){
}

void PlayState::update(Game* g, double d){

}

void PlayState::clean(){
}
