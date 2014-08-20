#include "MenuState.h"
#include "Game.h"

MenuState::MenuState(){}

void MenuState::init(Game* g){
	background = g->getTexture("red.bmp");
	MenuButton playButton{ "Play", 1, { 100, 100, 300, 100 }, { 255, 255, 255, 255 }, g };
	MenuButton exitButton{ "Exit", 2, { 100, 300, 300, 100 }, { 255, 255, 255, 255 }, g };
	buttons.push_back(playButton);
	buttons.push_back(exitButton);
	selectedButton = 1;
}

void MenuState::handleEvent(Game* g){
	menuInput = NONE;

	if (g->input->isPressed(SDLK_SPACE))
		menuInput = ACCEPT;

	if (g->input->isPressed(SDLK_UP))
		menuInput = UP;

	if (g->input->isPressed(SDLK_DOWN))
		menuInput = DOWN;

	if (g->input->isPressed(SDLK_ESCAPE))
		menuInput = EXIT;
}

void MenuState::draw(Game* g){
	g->gfx->drawFullBG(background);

	for (it = buttons.begin(); it != buttons.end(); ++it){
		it->draw(g, selectedButton);
	}
}

void MenuState::update(Game* g, double d){
	if (menuInput == UP && selectedButton != 1)
		selectedButton -= 1;

	if (menuInput == DOWN && selectedButton != 2)
		selectedButton += 1;


	if (menuInput == EXIT){
		g->core.exit();
	}
}

MenuButton::MenuButton(const char* text_, int buttonID_, SDL_Rect position_, SDL_Color c, Game* g){
	texture = g->getTextTexture(text_, g->getFont(), c);
	buttonID = buttonID_;
	position = position_;
	outerBorder.h = position.h + 30;
	outerBorder.w = position.w + 30;
	outerBorder.x = position.x - 15;
	outerBorder.y = position.y - 15;
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

void MenuState::clean(){
	SDL_DestroyTexture(background);

	while (!buttons.empty()){
		buttons.back().clean();
		buttons.pop_back();
	}
}

void MenuButton::clean(){
	SDL_DestroyTexture(texture);
}