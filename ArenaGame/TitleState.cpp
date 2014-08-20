#include "TitleState.h"
#include "Game.h"

TitleState::TitleState() : titleInput(NONE){}

void TitleState::init(Game* g){
	colour = { 30, 200, 70, 255 };
	titleRect = g->setRectToMiddle(350, 130);
	welcomeRect = titleRect;
	welcomeRect.y += (titleRect.y + 10);
	welcomeRect.h -= 75;
	title = g->getTextTexture("TITLE SCREEN!", g->getFont(), colour);
	welcomeMessage = g->getTextTexture("Press any key to continue..", g->getFont(), colour);
	background = g->getTexture("res/titleBackground.png");
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
	g->gfx->draw(title, titleRect);
	g->gfx->draw(welcomeMessage, welcomeRect);
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
	SDL_DestroyTexture(welcomeMessage);
}