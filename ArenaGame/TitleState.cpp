#include "TitleState.h"
#include "Game.h"

TitleState::TitleState(){}

void TitleState::init(Game* g){
	int h = g->gfx->getWindowHeight();
	int w = g->gfx->getWindowWidth();
	int size = 200;
	middle = { ((w / 2) - size / 2), ((h / 2) - size / 2), size, size }; //SDL rect set to center of screen
	colour = { 255, 255, 255, 255 };

	title = g->getTextTexture("TITLE SCREEN!", g->getFont(), colour);
	background = g->getTexture("yel.bmp");
}

void TitleState::handleEvent(Game* g){
	if (g->input->isPressed(SDLK_SPACE))
		g->pushState(&g->mainMenu);

	if (g->input->isPressed(SDLK_ESCAPE))
		g->core.exit();
}

void TitleState::draw(Game* g){
	g->gfx->drawFullBG(background);
	g->gfx->draw(title, middle);
}

void TitleState::update(Game* g, double d){
}

void TitleState::clean(){
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(background);
}