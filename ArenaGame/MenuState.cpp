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
	setBackgroundImage(ResourceLoader::getResource("titleBG"));
	setBorderColour({ 60, 60, 60, 255 });
	setSelBorderColour({ 30, 130, 230, 255 });
	setItemBgColour({ 200, 200, 200, 255 });
	int screenPortionH = gfx->getWindowHeight() / 10;
	int screenPortionW = gfx->getWindowWidth() / 10;

	SDL_Rect posRect = { (screenPortionW * 3.5), (screenPortionH * 3), (screenPortionW*3), (screenPortionH * 2) };
	playButton.setTexture(ResourceLoader::getResource("playText")).setFunc(goToCharSelect).setID(0).setPosition(posRect).setBorderSize(10);
	
	posRect = { screenPortionW*3, screenPortionH*5+20, screenPortionW, screenPortionH };
	optionsButton.setTexture(ResourceLoader::getResource("optionsText")).setFunc(goToOptions).setID(1).setPosition(posRect).setBorderSize(10);

	posRect = { (screenPortionW * 5) - (screenPortionW/2), screenPortionH * 5 + 20, screenPortionW, screenPortionH };
	libraryButton.setTexture(ResourceLoader::getResource("libraryText")).setFunc(goToLibrary).setID(2).setPosition(posRect).setBorderSize(10);

	posRect = { screenPortionW * 6, screenPortionH * 5 + 20, screenPortionW, screenPortionH };
	exitButton.setTexture(ResourceLoader::getResource("exitText")).setFunc(exit).setID(3).setPosition(posRect).setBorderSize(10);

	addButton(&playButton);
	addButton(&optionsButton);
	addButton(&libraryButton);
	addButton(&exitButton);
}

void MenuState::update(double d){
	//modified to work with the weird layout of my main menu screen
	switch (menuInput){
	case ACCEPT:
		for (auto button : buttons){
			if (button->getID() == selectedButton){
				buttons[selectedButton]->execute();
				selectedButton = 0;
			}
		}
		break;
	case BACK:
		StateManager::instance().popState();
		break;
	case UP:
		if (selectedButton != 0)
			selectedButton = 0;
		break;
	case DOWN:
		if (selectedButton == 0)
			selectedButton++;
		if (selectedButton != (buttons.size() - 1))
			selectedButton++;
		break;
	case LEFT:
		if (selectedButton == 0){
			selectedButton = 1;
		} else {
			if (selectedButton != 0)
				selectedButton--;
		}
		break;
	case RIGHT:
		if (selectedButton == 0){
			selectedButton = 3;
		}
		else {
			if (selectedButton != (buttons.size() -1))
				selectedButton++;
		}
		break;
	case EXIT:
		InputManager::instance()->quit();
		break;
	default:
		break;
	}
}

void OptionsState::init(){
	setBackgroundImage(ResourceLoader::getResource("titleBG"));
	setBorderColour({ 60, 60, 60, 255 });
	setSelBorderColour({ 30, 130, 230, 255 });
	setItemBgColour({ 200, 200, 200, 255 });
	int screenPortionH = gfx->getWindowHeight() / 10;
	int screenPortionW = gfx->getWindowWidth() / 10;

	menuBG.setTexture(ResourceLoader::getResource("menuBG")).setPosition({ screenPortionW * 2, screenPortionH * 2.5, gfx->getWindowWidth() - (screenPortionW * 4), gfx->getWindowHeight() - (screenPortionH * 4) });
	title.setTexture(ResourceLoader::getResource("optionsText")).setPosition({ screenPortionW * 5 - ((screenPortionW *1.5)/ 2), 20, screenPortionW*1.5, screenPortionH *1.5});

	posRect = { screenPortionW * 3, screenPortionH * 3, (screenPortionW*1.5), (screenPortionH * 1.2) };
	fullscreen.setTexture(ResourceLoader::getResource("fullscreenText")).setPosition(posRect);
	posRect.y += (screenPortionH * 1.2) + 20;
	res.setTexture(ResourceLoader::getResource("resolutionText")).setPosition(posRect);

	posRect = { screenPortionW * 6, screenPortionH * 3, (screenPortionW), (screenPortionH) };
	fullscreenTog.setAltColour({ 255, 0, 0, 255 }).setOnColour({ 0, 255, 0, 255 }).setID(0).setPosition(posRect).setBorderSize(10);

	if (Settings::instance().getSetting("fullscreen") == "true"){
		fullscreenTog.setToggle(true);
	}	else {
		fullscreenTog.setToggle(false);
	}

	posRect = { (screenPortionW * 5 - (screenPortionW * 1.2)-15), screenPortionH*8, (screenPortionW*1.2), (screenPortionH * 1.2) };
	acceptButton.setTexture(ResourceLoader::getResource("acceptText")).setFunc(goBack).setID(1).setPosition(posRect).setBorderSize(10);
	posRect.x += (screenPortionW*1.2) + 15;
	backButton.setTexture(ResourceLoader::getResource("backText")).setFunc(goBack).setID(2).setPosition(posRect).setBorderSize(10);
	
	addItem(&menuBG);
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
				goBack();	//pops twice (all the way back to title), cleaning all states along the way and reinitializing title state at correct resolution
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
	setBackgroundImage(ResourceLoader::getResource("titleBG"));
	setBorderColour({ 60, 60, 60, 255 });
	setSelBorderColour({ 30, 130, 230, 255 });
	setItemBgColour({ 200, 200, 200, 255 });
	
	SDL_Rect posRect = { gfx->getWindowWidth() / 2 - 100, 10, 200, 75 };
	title.setTexture(ResourceLoader::getResource("libraryText")).setPosition(posRect);

	posRect = { gfx->getWindowWidth() / 2 - 40, gfx->getWindowHeight()-70, 80, 50 };
	backButton.setTexture(ResourceLoader::getResource("backText")).setFunc(goBack).setID(0).setPosition(posRect).setBorderSize(10);
	addItem(&title);
	addButton(&backButton);
}