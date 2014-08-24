#include "MenuSystem.h"
#include "../ArenaGame/Game.h"

MenuSystem::MenuSystem() : selectedButton(0), menuInput(NONE){}

void MenuSystem::init(Game* g){}

void MenuSystem::handleEvent(Game* g){
	menuInput = NONE;

	if (g->input->isPressed(SDLK_SPACE) || g->input->isPressed(SDLK_RETURN))
		menuInput = ACCEPT;

	if (g->input->isPressed(SDLK_ESCAPE))
		menuInput = BACK;

	if (g->input->isPressed(SDLK_UP) || g->input->isPressed(SDLK_w))
		menuInput = UP;

	if (g->input->isPressed(SDLK_LEFT) || g->input->isPressed(SDLK_a))
		menuInput = LEFT;

	if (g->input->isPressed(SDLK_RIGHT) || g->input->isPressed(SDLK_d))
		menuInput = RIGHT;

	if (g->input->isPressed(SDLK_DOWN) || g->input->isPressed(SDLK_s))
		menuInput = DOWN;
}

void MenuSystem::draw(Game* g){
	g->gfx->drawFullBG(background);

	for (auto item: items){
		item->draw(g);
	}

	for (auto button: buttons){
		button->draw(g, selectedButton);
	}
}

void MenuSystem::update(Game* g, double d){
	switch (menuInput){
	case ACCEPT:
		buttons[selectedButton]->execute(g);
		selectedButton = 0;
		break;
	case BACK:
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

void MenuSystem::setBackgroundImage(SDL_Texture* t){
	background = t;
}

void MenuSystem::addButton(ExecutableMenuItem * m){
	buttons.push_back(m);
}

void MenuSystem::addItem(MenuItem* i){
	items.push_back(i);
}

void MenuSystem::setTextColour(SDL_Color c){
	menuTextCol = c;
}

SDL_Color MenuSystem::getTextColour(){
	return menuTextCol;
}

void MenuSystem::clean(){
	SDL_DestroyTexture(background);

	while (!items.empty()){
		items.back()->clean();
		items.pop_back();
	}
	while (!buttons.empty()){
		buttons.back()->clean();
		buttons.pop_back();
	}
}
