#include "MenuState.h"

void goBack(){
	StateManager::instance().popState();
}

void goToCharSelect(){
	CharSelectState * charSel = new CharSelectState();
	StateManager::instance().pushState(charSel);
}

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

	playButton.setID(0).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("PLAY", gfx).setFunc(goToCharSelect);
	posRect.y += 90;
	posRect.x -= 200;
	optionsButton.setID(1).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("OPTIONS", gfx).setFunc(goToOptions);
	posRect.x += 200;
	libraryButton.setID(2).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("LIBRARY", gfx).setFunc(goToLibrary);
	posRect.x += 200;
	exitButton.setID(3).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("EXIT", gfx).setFunc(exit);


	addButton(&playButton);
	addButton(&optionsButton);
	addButton(&libraryButton);
	addButton(&exitButton);
}

void OptionsState::init(){
	setBackgroundImage(gfx->makeTextureFromSurf(ResourceLoader::instance().loadImage("res/titleBackground.png")));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({ 0, 100, 0, 55 });
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });
	
	posRect = { gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	title.setTexture("OPTIONS", getTextColour(), gfx).setPosition(posRect);
	posRect = { 40, 95, 150, 50 };
	fullscreen.setTexture("Fullscreen", getTextColour(),gfx).setPosition(posRect);
	posRect.y += 60;
	res.setTexture("Resolution", getTextColour(), gfx).setPosition(posRect);

	posRect = { gfx->getWindowWidth() - 190, 95, 150, 50 };
	fullscreenTog = { 0, posRect, { 0, 255, 0, 255 }, { 255, 0, 0, 255 } };

	if (Settings::instance().getSetting("fullscreen") == "true"){
		fullscreenTog.setToggle(true);
	}	else {
		fullscreenTog.setToggle(false);
	}

	posRect = { gfx->getWindowWidth() / 2 - 100, gfx->getWindowHeight() - 70, 80, 50 };
	acceptButton.setID(1).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("ACCEPT", gfx).setFunc(goBack);
	posRect = { gfx->getWindowWidth()/2 + 20, gfx->getWindowHeight() - 70, 80, 50 };
	backButton.setID(2).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("BACK", gfx).setFunc(goBack);

	addItem(&title);
	addItem(&fullscreen);
	addItem(&res);
	addButton(&fullscreenTog);
	addButton(&backButton);
	addButton(&acceptButton);
}

void OptionsState::update(double d){
	switch (menuInput){
		case ACCEPT:
			buttons[selectedButton]->execute();
			
			if (selectedButton == acceptButton.getID()){
				gfx->setFullscreen(fullscreenTog.getToggle());
				goBack();
				StateManager::instance().getState()->clean();
				StateManager::instance().getState()->init();
			}
			selectedButton = 0;
			break;
		case BACK:
			goBack();
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
			InputManager::instance()->quit();
			break;
		case NONE:
		default:
			break;							
	}
}

void LibraryState::init(){
	setBackgroundImage(gfx->makeTextureFromSurf(ResourceLoader::instance().loadImage("res/titleBackground.png")));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({ 0, 100, 0, 55 });
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });
	
	SDL_Rect posRect = { gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	title = { posRect, "LIBRARY", getTextColour(), gfx };
	posRect = { gfx->getWindowWidth() / 2 - 40, gfx->getWindowHeight()-70, 80, 50 };
	backButton.setID(0).setPosition(posRect).setBorderSize(10).setFontColour(getTextColour()).setTexture("BACK", gfx).setFunc(goBack);
	addItem(&title);
	addButton(&backButton);
}