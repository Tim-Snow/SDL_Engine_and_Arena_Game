#include "TitleState.h"
#include "Game.h"

TitleState::TitleState() : titleInput(NONE){}

void TitleState::init(Game* g){
	colour = { 255, 255, 255, 255 };
	middle = g->setRectToMiddle(200);
	title = g->getTextTexture("TITLE SCREEN!", g->getFont(), colour);
	background = g->getTexture("yel.bmp");
}

void TitleState::handleEvent(Game* g){
	titleInput = NONE;

	if (g->input->isAnyKeyPressed())
		titleInput = ACCEPT;

	if (g->input->isPressed(SDLK_ESCAPE))
		titleInput = EXIT;
}

void TitleState::draw(Game* g){
	g->gfx->drawFullBG(background);
	g->gfx->draw(title, middle);
}

void TitleState::update(Game* g, double d){
	if (titleInput == ACCEPT){
		g->pushState(&g->mainMenu);
		titleInput = NONE;
	}

	if (titleInput == EXIT){
		g->core.exit();
	}
}

void TitleState::clean(){
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(background);
}