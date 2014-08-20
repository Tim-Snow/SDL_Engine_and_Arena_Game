#include "MenuState.h"
#include "Game.h"

MenuState::MenuState(){}

void MenuState::init(Game* g){
	background = g->getTexture("res/titleBackground.png");
	menuTextCol = { 255, 255, 255, 255 };
	MenuButton playButton	{ "Play",	 1, { 50, 50,  150, 50 }, menuTextCol, g };
	MenuButton optionsButton{ "Options", 2, { 50, 150, 150, 50 }, menuTextCol, g };
	MenuButton exitButton	{ "Exit",	 3, { 50, 250, 150, 50 }, menuTextCol, g };
	buttons.push_back(playButton);
	buttons.push_back(optionsButton);
	buttons.push_back(exitButton);
	selectedButton = 1;
	menuInput = NONE;
}

void MenuState::handleEvent(Game* g){
	menuInput = NONE;

	if (g->input->isPressed(SDLK_SPACE) || g->input->isPressed(SDLK_RETURN))
		menuInput = ACCEPT;

	if (g->input->isPressed(SDLK_BACKSPACE))
		menuInput = BACK;

	if (g->input->isPressed(SDLK_UP) || g->input->isPressed(SDLK_LEFT) || g->input->isPressed(SDLK_w) || g->input->isPressed(SDLK_a))
		menuInput = UP;

	if (g->input->isPressed(SDLK_DOWN) || g->input->isPressed(SDLK_RIGHT) || g->input->isPressed(SDLK_s) || g->input->isPressed(SDLK_d))
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
	if (selectedButton == 1 && menuInput == ACCEPT)
		g->pushState(&g->playGame);
	
	if (menuInput == UP && selectedButton != 1)
		selectedButton -= 1;

	if (menuInput == DOWN && selectedButton != 3)
		selectedButton += 1;

	if (menuInput == BACK){
		g->popState();
		menuInput = NONE;
	}

	if (menuInput == EXIT || (menuInput == ACCEPT && selectedButton == 3)){
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