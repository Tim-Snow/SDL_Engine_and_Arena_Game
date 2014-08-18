#include "TitleState.h"
#include "Game.h"

TitleState::TitleState(){}

void TitleState::init(){
	tsBackground = Game::instance()->getTexture("yel.bmp");
}

void TitleState::handleEvent(Game* g){
	g->input->pollEvent();

	if (g->input->isPressed(SDLK_SPACE))
		g->pushState(&MenuState::instance());

	if (g->input->isPressed(SDLK_ESCAPE))
		g->core.exit();
}

void TitleState::draw(Game* g){
	g->gfx->drawFullBG(tsBackground);
}

void TitleState::update(Game* g, double d){
}

void TitleState::clean(){
	SDL_DestroyTexture(tsBackground);
}