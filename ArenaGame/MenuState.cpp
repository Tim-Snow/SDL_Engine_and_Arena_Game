#include "MenuState.h"
#include "Game.h"


MenuState::MenuState(){}


void MenuState::init(Game* g){
	mBackground = g->getTexture("red.bmp");
}

void MenuState::handleEvent(Game* g){
	if (g->input->isPressed(SDLK_SPACE))
		g->pushState(&g->playGame);

	if (g->input->isPressed(SDLK_ESCAPE))
		g->core.exit();
}

void MenuState::draw(Game* g){
	g->gfx->drawFullBG(mBackground);
}

void MenuState::update(Game* g, double d){
}

void MenuState::clean(){
	SDL_DestroyTexture(mBackground);
}
