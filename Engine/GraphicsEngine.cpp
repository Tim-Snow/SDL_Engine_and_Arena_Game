#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() : name("SDL2.0 Engine created by Tim Snow"){}

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

void GraphicsEngine::draw(AbstractGameObj * g){
	SDL_RenderCopy(renderer, g->getTexture(), NULL, &g->getRect());
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

SDL_Texture * GraphicsEngine::renderText(const std::string &text, const std::string &font, SDL_Color colour, int size){
	TTF_Font *f = TTF_OpenFont(font.c_str(), size);
	SDL_Surface *surf = TTF_RenderText_Blended(f, text.c_str(), colour);
	texture = makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(f);
	return texture;
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

GraphicsEngine::~GraphicsEngine(){
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}