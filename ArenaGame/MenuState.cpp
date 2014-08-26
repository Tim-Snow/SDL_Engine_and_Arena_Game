#include "MenuState.h"

void goToOptions(){
	OptionsState * optionsMenu = new OptionsState();
	StateManager::instance().pushState(optionsMenu);
}

void goToLibrary(){
	LibraryState * libMenu = new LibraryState();
	StateManager::instance().pushState(libMenu);
}

void exit(){
	InputManager::instance()->quit();
}

void MenuState::init(){
	setBackgroundImage(gfx->makeTextureFromSurf(ResourceLoader::instance().loadImage("res/titleBackground.png")));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({0, 100, 0, 55});
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });

	SDL_Rect posRect = { (gfx->getWindowWidth() / 2) - 75, gfx->getWindowHeight() - 160, 150, 50 };

	playButton = new MenuButton();
	playButton->setID(0).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("PLAY", gfx);
	posRect.y += 90;
	posRect.x -= 200;
	optionsButton = new MenuButton();
	optionsButton->setID(1).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("OPTIONS", gfx).setFunc(goToOptions);
	posRect.x += 200;
	libraryButton = new MenuButton();
	libraryButton->setID(2).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("LIBRARY", gfx).setFunc(goToLibrary);
	posRect.x += 200;
	exitButton = new MenuButton();
	exitButton->setID(3).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("EXIT", gfx).setFunc(exit);


	addButton(playButton);
	addButton(optionsButton);
	addButton(libraryButton);
	addButton(exitButton);
}

void OptionsState::init(){
	/*setBackgroundImage(g->getTexture("res/titleBackground.png"));
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
	addButton(acceptButton);*/
}

void LibraryState::init(){
	/*setBackgroundImage(g->getTexture("res/titleBackground.png"));
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
	addButton(backButton);*/
}