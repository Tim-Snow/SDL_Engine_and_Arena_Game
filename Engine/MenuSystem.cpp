#include "MenuSystem.h"
#include "../ArenaGame/Game.h"

void MenuSystem::init(){}

void MenuSystem::handleEvent(){
	menuInput = NONE;

	if (input->isPressed(SDLK_SPACE) || input->isPressed(SDLK_RETURN))
		menuInput = ACCEPT;

	if (input->isPressed(SDLK_ESCAPE))
		menuInput = BACK;

	if (input->isPressed(SDLK_UP) || input->isPressed(SDLK_w))
		menuInput = UP;

	if (input->isPressed(SDLK_LEFT) || input->isPressed(SDLK_a))
		menuInput = LEFT;

	if (input->isPressed(SDLK_RIGHT) || input->isPressed(SDLK_d))
		menuInput = RIGHT;

	if (input->isPressed(SDLK_DOWN) || input->isPressed(SDLK_s))
		menuInput = DOWN;
}

void MenuSystem::draw(){
	gfx->drawFullBG(background);

	for (auto item: items){
		item->draw(gfx);
	}

	for (auto button: buttons){
		button->draw(gfx, selectedButton);
	}
}

void MenuSystem::update(double d){
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
	default:
		break;
	}
}

void MenuSystem::addButton(ExecutableMenuItem * m){
	m->setBackgroundColour(itemBgCol);
	m->setBorderCol(borderCol);
	m->setSelBorderCol(selBorderCol);
	buttons.push_back(m);
}

void MenuSystem::addItem(MenuItem* i){
	items.push_back(i);
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
