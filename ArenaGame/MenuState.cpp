#include "MenuState.h"
#include "Game.h"

void MenuState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });

	SDL_Rect posRect = { (g->gfx->getWindowWidth()/2) - 75, g->gfx->getWindowHeight() - 160 ,150, 50 };
	MenuButton * playButton = new MenuButton{ "PLAY", 0, &playState, posRect, getTextColour(), g };
	posRect.y += 90;
	posRect.x -= 200;
	MenuButton * optionsButton = new MenuButton{ "OPTIONS", 1, &optionsState, posRect, getTextColour(), g };
	posRect.x += 200;
	MenuButton * libraryButton = new MenuButton{ "LIBRARY", 2, &libraryState, posRect, getTextColour(), g };
	posRect.x += 200;
	MenuButton * exitButton = new MenuButton{ "EXIT", 3, NULL, posRect, getTextColour(), g };
	addButton(playButton);
	addButton(optionsButton);
	addButton(libraryButton);
	addButton(exitButton);
}

void OptionsState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });


	posRect = { 40, 95, 150, 50 };
	TextureItem * fullscreen = new TextureItem{ posRect, "Fullscreen", getTextColour(), g };

	posRect.y += 60;
	TextureItem * res = new TextureItem{ posRect, "Resolution", getTextColour(), g };
	posRect = { g->gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	title = new TextureItem{ posRect, "OPTIONS", getTextColour(), g };
	posRect = { g->gfx->getWindowWidth() - 190, 95, 150, 50 };


	fullscreenTog = new ToggleButton{ 0, posRect, { 255, 255, 255, 255 }, { 0, 0, 0, 255 } };

	if (Settings::instance().getSetting("fullscreen") == "true"){
		fullscreenTog->setToggle(true);
	}	else {
		fullscreenTog->setToggle(false);
	}

	posRect = { g->gfx->getWindowWidth() / 2 - 100, g->gfx->getWindowHeight() - 70, 80, 50 };
	acceptButton = new MenuButton{ "ACCEPT", 1, &g->acceptState, posRect, getTextColour(), g };

	posRect = { g->gfx->getWindowWidth()/2 + 20, g->gfx->getWindowHeight() - 70, 80, 50 };
	MenuButton * backButton = new MenuButton{ "BACK", 2, &g->backState, posRect, getTextColour(), g };
	
	addItem(title);
	addItem(fullscreen);
	addItem(res);
	addButton(fullscreenTog);
	addButton(backButton);
	addButton(acceptButton);
}

void OptionsState::update(Game* g, double d){
	switch (menuInput){
	case ACCEPT:
		buttons[selectedButton]->execute(g);

		if (selectedButton == acceptButton->getID()){
			g->gfx->setFullscreen(fullscreenTog->getToggle());
			g->getState()->clean();
			g->getState()->init(g);
		}

		selectedButton = 0;
		break;
	case BACK:
		if (Settings::instance().getSetting("fullscreen") == "true"){
			g->gfx->setFullscreen(true);
		} else {
			g->gfx->setFullscreen(false);
		}

		g->popState();
		break;
	case LEFT:
	case UP:
		if (selectedButton != 0)
			selectedButton--;
		break;
	case RIGHT:
	case DOWN:
		if (selectedButton != (buttons.size() - 1))
			selectedButton++;
		break;
	case EXIT:
		g->core.exit();
		break;
	default:
		break;
	}
}

void LibraryState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 30, 255 });
	SDL_Rect posRect = { g->gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	TextureItem * title = new TextureItem{ posRect, "LIBRARY", getTextColour(), g};
	posRect = { g->gfx->getWindowWidth() / 2 - 40, g->gfx->getWindowHeight()-70, 80, 50 };
	MenuButton * backButton = new MenuButton{ "BACK", 0, &g->backState, posRect, getTextColour(), g };
	addItem(title);
	addButton(backButton);
}