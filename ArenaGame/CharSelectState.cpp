#include "CharSelectState.h"

CharSelectState::CharSelectState(){}

void CharSelectState::init(){
	setBackgroundImage(ResourceLoader::getResource("menuBG"));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({ 0, 100, 0, 55 });
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });

	title = { { gfx->getWindowWidth() / 2 - 100, 10, 200, 75 }, "Char Select", getTextColour(), gfx };

	addItem(&title);
}

void CharSelectState::update(double d){
	if (menuInput == BACK)
		StateManager::instance().popState();
}
