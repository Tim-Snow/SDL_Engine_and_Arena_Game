#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() : name("SDL2.0 Engine created by Tim Snow"), fullscreen(false){}

void GraphicsEngine::setTitle(std::string n){
	SDL_SetWindowTitle(window, n.c_str());
}

bool GraphicsEngine::makeWindow(int width, int height){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return false; }

	if (TTF_Init() != 0){ return false; }

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) { return false; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) { return false; }

	return true;
}

void GraphicsEngine::toggleFullscreen(){
	if (fullscreen){
		fullscreen = false;
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		SDL_SetWindowSize(window, 640, 480);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}	else {
		fullscreen = true;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	
}

void GraphicsEngine::draw(SDL_Texture * t, SDL_Rect r){
	SDL_RenderCopy(renderer, t, NULL, &r);
}

void GraphicsEngine::drawFullBG(SDL_Texture * t){
	SDL_Rect r = { 0, 0, getWindowWidth(), getWindowHeight() };
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

int GraphicsEngine::getWindowHeight(){
	int h;
	SDL_GetWindowSize(window, NULL, &h);
	return h;
}

int GraphicsEngine::getWindowWidth(){
	int w;
	SDL_GetWindowSize(window, &w, NULL);
	return w;
}

void GraphicsEngine::setWindowSize(int w, int h){
	SDL_SetWindowSize(window, w, h);
}

GraphicsEngine::~GraphicsEngine(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}