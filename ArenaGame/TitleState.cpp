#include "TitleState.h"

void goToMenu(){
	MenuState * mainMenu = new MenuState();
	StateManager::instance().pushState(mainMenu);
}

void TitleState::init(){
	setBackgroundImage(ResourceLoader::getResource("menuBG"));
	//background = 
	//setBackgroundImage();
	setTextColour({ 30, 200, 30, 255 });

	SDL_Rect mid = gfx->setRectToMiddle(350, 150);
	titleMessage.setTexture("Arena Game!", getTextColour(), gfx).setPosition(mid);
	mid = gfx->setRectToMiddle(200, 50);
	mid.y += 100;
	welcomeMessage.setTexture("Press any key..!", getTextColour(), gfx).setPosition(mid);
	
	addItem(&titleMessage);
	addItem(&welcomeMessage);
}


void TitleState::handleEvent(){
	menuInput = NONE;

	if (input->isAnyKeyPressed())
		menuInput = ACCEPT;

	if (input->isPressed(SDLK_ESCAPE) || input->isControllerPressed(SDL_CONTROLLER_BUTTON_B))
		menuInput = EXIT;
}

void TitleState::update(double d){
	if (menuInput == ACCEPT){
		goToMenu();
	}

	if (menuInput == EXIT){
		input->quit();
	}

}