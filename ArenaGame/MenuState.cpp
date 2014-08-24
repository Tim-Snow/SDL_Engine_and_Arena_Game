#include "MenuState.h"
#include "Game.h"

void MenuState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({0, 100, 0, 55});
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });

	SDL_Rect posRect = { (g->gfx->getWindowWidth() / 2) - 75, g->gfx->getWindowHeight() - 160, 150, 50 };


	playButton = new MenuButton();
	playButton->setID(0).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("PLAY", g).setState(&charSelect);
	posRect.y += 90;
	posRect.x -= 200;
	optionsButton = new MenuButton();
	optionsButton->setID(1).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("OPTIONS", g).setState(&optionsState);
	posRect.x += 200;
	libraryButton = new MenuButton();
	libraryButton->setID(2).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("LIBRARY", g).setState(&libraryState);
	posRect.x += 200;
	exitButton = new MenuButton();
	exitButton->setID(3).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("EXIT", g);


	addButton(playButton);
	addButton(optionsButton);
	addButton(libraryButton);
	addButton(exitButton);
}

void OptionsState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({ 0, 100, 0, 55 });
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });
	
	
	posRect = { 40, 95, 150, 50 };
	fullscreen = new TextureItem{ posRect, "Fullscreen", getTextColour(), g };
	posRect.y += 60;
	res = new TextureItem{ posRect, "Resolution", getTextColour(), g };
	posRect = { g->gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	title = new TextureItem{ posRect, "OPTIONS", getTextColour(), g };
	posRect = { g->gfx->getWindowWidth() - 190, 95, 150, 50 };


	fullscreenTog = new ToggleButton{ 0, posRect, { 0, 255, 0, 255 }, { 255, 0, 0, 255 } };

	if (Settings::instance().getSetting("fullscreen") == "true"){
		fullscreenTog->setToggle(true);
	}	else {
		fullscreenTog->setToggle(false);
	}
	posRect = { g->gfx->getWindowWidth() / 2 - 100, g->gfx->getWindowHeight() - 70, 80, 50 };
	acceptButton = new MenuButton();
	acceptButton->setID(1).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("ACCEPT", g).setState(&g->backState);
	posRect = { g->gfx->getWindowWidth()/2 + 20, g->gfx->getWindowHeight() - 70, 80, 50 };
	backButton = new MenuButton();
	backButton->setID(2).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("BACK", g).setState(&g->backState);

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
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({ 0, 100, 0, 55 });
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });
	
	SDL_Rect posRect = { g->gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	title = new TextureItem{ posRect, "LIBRARY", getTextColour(), g};
	posRect = { g->gfx->getWindowWidth() / 2 - 40, g->gfx->getWindowHeight()-70, 80, 50 };
	backButton = new MenuButton();
	backButton->setID(0).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("BACK", g).setState(&g->backState);
	addItem(title);
	addButton(backButton);
}