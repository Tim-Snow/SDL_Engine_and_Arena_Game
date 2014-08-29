#include "TitleState.h"

void goToMenu(){
	MenuState * mainMenu = new MenuState();
	StateManager::instance().pushState(mainMenu);
}

void TitleState::init(){
	setBackgroundImage(ResourceLoader::getResource("titleBG"));

	SDL_Rect mid = gfx->setRectToMiddle(400, 130); mid.y -= 50;
	titleMessage.setTexture(ResourceLoader::getResource("titleText")).setPosition(mid);
	mid = gfx->setRectToMiddle(350, 60);	mid.y += 50;
	welcomeMessage.setTexture(ResourceLoader::getResource("anykeyText")).setPosition(mid);
	
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