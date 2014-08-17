#include "MenuState.h"
#include "Game.h"

MenuState::MenuState(){}

void MenuState::init(){}

void MenuState::handleEvent(Game* g){
	g->input->pollEvent();

	if (g->input->isPressed(SDLK_ESCAPE))
		g->core.exit();
}
void MenuState::draw(Game* g){
}

void MenuState::update(Game* g){}

void MenuState::clean(){}