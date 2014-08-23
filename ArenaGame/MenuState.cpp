#include "MenuState.h"
#include "Game.h"

void MenuState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });

	SDL_Rect posRect = { (g->gfx->getWindowWidth()/2) - 75, g->gfx->getWindowHeight() - 160 ,150, 50 };
	MenuButton playButton = MenuButton{ "PLAY", 0, &playState, posRect, getTextColour(), g };
	posRect.y += 90;
	posRect.x -= 200;
	MenuButton optionsButton = MenuButton{ "OPTIONS", 1, &optionsState, posRect, getTextColour(), g };
	posRect.x += 200;
	MenuButton libraryButton = MenuButton{ "LIBRARY", 2, &libraryState, posRect, getTextColour(), g };
	posRect.x += 200;
	MenuButton exitButton = MenuButton{ "EXIT", 3, NULL, posRect, getTextColour(), g };
	addButton(playButton);
	addButton(optionsButton);
	addButton(libraryButton);
	addButton(exitButton);
}

void OptionsState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });

	SDL_Rect posRect = { g->gfx->getWindowWidth() / 2 - 100, g->gfx->getWindowHeight() - 100, 80, 50 };
	MenuButton acceptButton = MenuButton{ "ACCEPT", 0, &g->backState, posRect, getTextColour(), g };

	posRect = { g->gfx->getWindowWidth()/2 + 20, g->gfx->getWindowHeight() - 100, 80, 50 };
	MenuButton backButton = MenuButton{ "BACK", 1, &g->backState, posRect, getTextColour(), g };

	addButton(backButton);
	addButton(acceptButton);
}

void LibraryState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });
	SDL_Rect posRect = { g->gfx->getWindowWidth()/2 -100, 50, 200, 100 };
	TextureItem * title = new TextureItem{ posRect, "LIBRARY", getTextColour(), g};
	posRect = { g->gfx->getWindowWidth() / 2 - 40, g->gfx->getWindowHeight()-100, 80, 50 };
	MenuButton backButton = MenuButton{ "BACK", 0, &g->backState, posRect, getTextColour(), g };
	addItem(title);
	addButton(backButton);
}