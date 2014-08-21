#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	pushState(&titleScreen);

	mainMenu.setTextColour({ 255, 255, 255, 255 });
	mainMenu.setBackgroundImage(getTexture("res/titleBackground.png"));
	MenuButton playButton	{ "Play",	 0, &playGame,    { 50,  50, 150, 50 }, mainMenu.getTextColour(), this };
	MenuButton optionsButton{ "Options", 1, &optionsMenu, { 50, 150, 150, 50 }, mainMenu.getTextColour(), this };
	MenuButton exitButton	{ "Exit",	 2, NULL,		  { 50, 250, 150, 50 }, mainMenu.getTextColour(), this };
	mainMenu.addButton(playButton);
	mainMenu.addButton(optionsButton);
	mainMenu.addButton(exitButton);

	optionsMenu.setTextColour({ 255, 255, 255, 255 });
	optionsMenu.setBackgroundImage(getTexture("res/titleBackground.png"));
	MenuButton backButton{ "Back", 0, &goBack, { 50, 50, 150, 50 }, optionsMenu.getTextColour(), this };
	optionsMenu.addButton(backButton);
}

void Game::handleEvent(){
	input->pollEvent();
	state.back()->handleEvent(this);
}

void Game::update(double d){
	state.back()->update(this, d);
}

void Game::draw(){
		gfx->clearDisplay();
		state.back()->draw(this);
		gfx->updateDisplay();
}

SDL_Texture * Game::getTexture(char* p){
	SDL_Surface* s = res->loadImage(p);
	texture = gfx->makeTextureFromSurf(s);
	SDL_FreeSurface(s);
	return texture;
}

SDL_Texture * Game::getTextTexture(const char* p, TTF_Font* f, SDL_Color c){
	SDL_Surface * surf = TTF_RenderText_Blended(f, p, c);
	texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

TTF_Font * Game::getFont(){
	if (font==nullptr)
		font = TTF_OpenFont("text.TTF", 64);

	return font;
}

SDL_Rect Game::setRectToMiddle(int sizeW_, int sizeH_){
	int h = gfx->getWindowHeight();
	int w = gfx->getWindowWidth();
	return{ ((w / 2) - sizeW_ / 2), ((h / 2) - sizeH_ / 2), sizeW_, sizeH_ };
}

void Game::pushState(State* s){
	state.push_back(s);
	handleEvent();
	state.back()->init(this);
}

void Game::popState(){
	if (!state.empty()){
		state.pop_back();
		handleEvent();
	}
}

Game::~Game(){
	while (!state.empty()){
		state.back()->clean();
		state.pop_back();
	}

	SDL_DestroyTexture(texture);
	core.exit();
}