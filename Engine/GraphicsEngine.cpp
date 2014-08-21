#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() : name("SDL2.0 Engine created by Tim Snow"), fullscreen(false){}

void GraphicsEngine::setTitle(std::string n){
	SDL_SetWindowTitle(window, n.c_str());
}

bool GraphicsEngine::makeWindow(int width, int height, bool fullscreen_){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return false; }

	if (TTF_Init() != 0){ return false; }
	
	if (fullscreen_){
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN;
		fullWidth = width; fullHeight = height;
		windowedWidth = 640; windowedHeight = 360;
	} else {
		flags = SDL_WINDOW_SHOWN;
		windowedWidth = width; windowedHeight = height;
		fullWidth = fullHeight = 0;
	}
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (window == nullptr) { return false; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) { return false; }

	return true;
}

void GraphicsEngine::toggleFullscreen(){
	if (fullscreen){
		fullscreen = false;
		Settings::instance().setSetting("fullscreen", "false");
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		SDL_SetWindowSize(window, windowedWidth, windowedHeight);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}	else {
		fullscreen = true;
		Settings::instance().setSetting("fullscreen", "true");
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_GetWindowSize(window, &fullWidth, &fullHeight);
	}
}

void GraphicsEngine::draw(SDL_Texture * t, SDL_Rect dest){
	SDL_RenderCopy(renderer, t, NULL, &dest);
}

void GraphicsEngine::drawFromSpritesheet(SDL_Texture* t, SDL_Rect src, SDL_Rect dest){
	SDL_RenderCopy(renderer, t, &src, &dest);
}

void GraphicsEngine::drawFullBG(SDL_Texture * t){
	SDL_Rect r;
	
	if (fullscreen){
		r = { 0, 0, fullWidth, fullHeight };
	} else {
		r = { 0, 0, windowedWidth, windowedHeight };
	}

	SDL_RenderCopy(renderer, t, NULL, &r);
}

SDL_Texture* GraphicsEngine::makeTextureFromSurf(SDL_Surface * s){
	texture = SDL_CreateTextureFromSurface(renderer, s);
	return texture;
}

void GraphicsEngine::clearDisplay(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void GraphicsEngine::updateDisplay(){
	SDL_RenderPresent(renderer);
}

void GraphicsEngine::drawSquare(int x, int y, int w, int r, int g, int b){
	SDL_Rect rect = { x, y, w, w };
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void GraphicsEngine::drawRect(int x, int y, int w, int h, int r, int g, int b){
	SDL_Rect rect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void GraphicsEngine::drawRect(SDL_Rect rect, int r, int g, int b){
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

int GraphicsEngine::getWindowHeight(){
	if (fullscreen)
		return fullHeight;
	else return windowedHeight;
}

int GraphicsEngine::getWindowWidth(){
	if (fullscreen)
		return fullWidth;
	else return windowedWidth;
}

void GraphicsEngine::setWindowSize(int w_, int h_){
	windowedWidth = w_; windowedHeight = h_;
	SDL_SetWindowSize(window, windowedWidth, windowedHeight);
	Settings::instance().setSetting("screenHeight", windowedHeight);
	Settings::instance().setSetting("screenWidth", windowedWidth);
}

GraphicsEngine::~GraphicsEngine(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}