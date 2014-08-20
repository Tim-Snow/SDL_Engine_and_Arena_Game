#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	pushState(&titleScreen);
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

SDL_Rect Game::setRectToMiddle(int size_){
	int h = gfx->getWindowHeight();
	int w = gfx->getWindowWidth();
	int size = size_;
	return { ((w / 2) - size / 2), ((h / 2) - size / 2), size, size };
}

void Game::pushState(State* s){
	state.push_back(s);
	handleEvent();
	state.back()->init(this);
}

void Game::popState(){
	if (!state.empty()){
		state.back()->clean();
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