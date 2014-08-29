#include "CharSelectState.h"

CharSelectState::CharSelectState(){}

void CharSelectState::init(){
	setBackgroundImage(ResourceLoader::getResource("titleBG"));
	setBorderColour({ 60, 60, 60, 255 });
	setSelBorderColour({ 150, 150, 150, 255 });
	setItemBgColour({ 200, 200, 200, 255 });
	test = InputManager::instance()->getController(0);
	SDL_Rect player1Quad = { (gfx->getWindowWidth() / 2) - (((gfx->getWindowWidth()/5)+10)*2), (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	SDL_Rect player2Quad = { (gfx->getWindowWidth() / 2) - ((gfx->getWindowWidth() / 5 ) + 5), (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	SDL_Rect player3Quad = { (gfx->getWindowWidth() / 2) + 5								 , (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	SDL_Rect player4Quad = { (gfx->getWindowWidth() / 2) + ((gfx->getWindowWidth() / 5) + 20), (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	a.setTexture(ResourceLoader::getResource("menuBG")).setPosition(player1Quad);
	b.setTexture(ResourceLoader::getResource("menuBG")).setPosition(player2Quad);
	c.setTexture(ResourceLoader::getResource("menuBG")).setPosition(player3Quad);
	d.setTexture(ResourceLoader::getResource("menuBG")).setPosition(player4Quad);
	title.setTexture(ResourceLoader::getResource("charSelText")).setPosition({ gfx->getWindowWidth() / 2 - 100, 10, 200, 75 });
	addItem(&title);
	addItem(&a);
	addItem(&b);
	addItem(&c);
	addItem(&d);
}

void CharSelectState::update(double d){
	if (InputManager::instance()->isControllerPressed(test, SDL_CONTROLLER_BUTTON_A))
		std::cout << "a" << std::endl;

	if (menuInput == BACK)
		StateManager::instance().popState();
}
