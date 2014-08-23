#include "TitleState.h"
#include "Game.h"

void TitleState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });

	SDL_Rect mid = g->setRectToMiddle(250, 150);
	TextureItem * titleMessage = new TextureItem{ mid, "Arena Game", getTextColour(), g };
	mid = g->setRectToMiddle(200, 50);
	mid.y += 100;
	TextureItem * welcomeMessage = new TextureItem{ mid, "Press any key..!", getTextColour(), g };
	
	addItem(titleMessage);
	addItem(welcomeMessage);
}

void TitleState::handleEvent(Game* g){
	titleInput = NONE;

	if (g->input->isAnyKeyPressed())
		titleInput = ACCEPT;

	if (g->input->isPressed(SDLK_ESCAPE))
		titleInput = EXIT;
}

void TitleState::update(Game* g, double d){
	if (titleInput == ACCEPT){
		g->pushState(&mainMenu);
		titleInput = NONE;
	}

	if (titleInput == EXIT){
		g->core.exit();
	}
}
