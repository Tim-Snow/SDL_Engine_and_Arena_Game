#include "MenuState.h"
#include "Game.h"

MenuState::MenuState(){}

void MenuState::init(Game* g){
	selectedButton = 0;
	menuInput = NONE;
}

void MenuState::handleEvent(Game* g){
	menuInput = NONE;

	if (g->input->isPressed(SDLK_SPACE) || g->input->isPressed(SDLK_RETURN))
		menuInput = ACCEPT;

	if (g->input->isPressed(SDLK_BACKSPACE))
		menuInput = BACK;

	if (g->input->isPressed(SDLK_UP) || g->input->isPressed(SDLK_w))
		menuInput = UP;

	if (g->input->isPressed(SDLK_LEFT) || g->input->isPressed(SDLK_a))
		menuInput = LEFT;

	if (g->input->isPressed(SDLK_RIGHT) || g->input->isPressed(SDLK_d))
		menuInput = RIGHT;

	if (g->input->isPressed(SDLK_DOWN) || g->input->isPressed(SDLK_s))
		menuInput = DOWN;

	if (g->input->isPressed(SDLK_ESCAPE))
		menuInput = EXIT;
}

void MenuState::draw(Game* g){
	g->gfx->drawFullBG(background);

	for (itemIt = items.begin(); itemIt != items.end(); ++itemIt){
		itemIt->draw(g);
	}

	for (buttonIt = buttons.begin(); buttonIt != buttons.end(); ++buttonIt){
		buttonIt->draw(g, selectedButton);
	}
}

void MenuState::update(Game* g, double d){
	if (menuInput == ACCEPT){
		buttons[selectedButton].execute(g);
		selectedButton = 0;
	}
	if (menuInput == BACK){
		g->popState();
		menuInput = NONE;
	}

	if (menuInput == LEFT  && selectedButton != 0)
		selectedButton -= 1;
	if (menuInput == RIGHT  && selectedButton != (buttons.size() - 1))
		selectedButton += 1;

	if (menuInput == UP && selectedButton != 0)
		selectedButton = 0;
	if (menuInput == DOWN && selectedButton != (buttons.size() - 1)){
		if (selectedButton == 0)
			selectedButton += 1;

	selectedButton += 1;
	}
	
	if (menuInput == EXIT)
		g->core.exit();
}

void MenuState::setBackgroundImage(SDL_Texture* t){
	background = t;
}

void MenuState::setTextColour(SDL_Color c){
	menuTextCol = c;
}

SDL_Color MenuState::getTextColour(){
	return menuTextCol;
}

void MenuState::addButton(MenuButton m){
	buttons.push_back(m);
}

void MenuState::addItem(MenuItem i){
	items.push_back(i);
}

void MenuState::clean(){
	SDL_DestroyTexture(background);

	while (!items.empty()){
		items.back().clean();
		items.pop_back();
	}

	while (!buttons.empty()){
		buttons.back().clean();
		buttons.pop_back();
	}
}

MenuButton::MenuButton(const char* text_, int buttonID_, State* state_, SDL_Rect position_, SDL_Color c, Game* g){
	texture = g->getTextTexture(text_, g->getFont(), c);
	nextState = state_;
	buttonID = buttonID_;
	position = position_;
	outerBorder.h = position.h + 30;
	outerBorder.w = position.w + 30;
	outerBorder.x = position.x - 15;
	outerBorder.y = position.y - 15;
}

void MenuButton::execute(Game* g){
	if (nextState == NULL){
		g->core.exit();
	} else if(nextState == &g->goBack) {
		g->popState();
	}
	else {
		g->pushState(nextState);
	}
}

void MenuButton::draw(Game* g, int i){
	if (i == buttonID){
		g->gfx->drawRect(outerBorder, 255, 255, 255);
	} else {
		g->gfx->drawRect(outerBorder, 30, 30, 30);
	}

	g->gfx->drawRect(position, 0, 0, 0);
	g->gfx->draw(texture, position);
}

void MenuItem::draw(Game* g) { 
	g->gfx->draw(texture, position); 
}

void MenuButton::clean(){
}