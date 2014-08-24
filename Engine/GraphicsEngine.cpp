#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() : name("SDL2.0 Engine created by Tim Snow"), fullscreen(false){}

void GraphicsEngine::getPossibleResolutions(){
	int i = 0;
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(i, &current);

	int ratio = gcd(current.w, current.h);
	int widthMult = current.w / ratio;
	int heightMult = (current.h / ratio);
	std::cout << "Aspect Ratio: " << widthMult << ":" << heightMult << std::endl;
	std::cout << "Possible resolutions: " << std::endl;
	std::cout << "Preset: " << std::endl;
	fullWidth = current.w;
	fullHeight = current.h;
	std::cout << current.w << ":" << current.h << " MAX RES" << std::endl;
	
	int width = 768; int height = 1024;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	width = 800, height = 600;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	width = 1024, height = 768;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	width = 1280, height = 1024;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	height = 720;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	width = 1366, height = 768;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	width = 1600, height = 900;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);
	width = 1680, height = 1050;
	if (width <= current.w || height <= current.h)
		Settings::instance().addResolution(width, height);

	std::cout << "CUSTOM" << std::endl;
	width = 0;
	int j = 0;
	while (width <= current.w){
		width = widthMult * j;
		if (width == 768 || width == 800 || width == 1024 || width == 1280 || width == 1360 || width == 1366 || width == 1400 || width == 1600 || width == 1680 || width == 1920)
			Settings::instance().addResolution(width, (heightMult * j));
		j++;
	}
}

int GraphicsEngine::gcd(int a, int b) {
	//found from 'paxdiablo' answer on: http://stackoverflow.com/questions/1186414/whats-the-algorithm-to-calculate-aspect-ratio-i-need-an-output-like-43-169
	return (b == 0) ? a : gcd(b, a%b);
}

void GraphicsEngine::setTitle(std::string n){
	SDL_SetWindowTitle(window, n.c_str());
}

bool GraphicsEngine::makeWindow(int width, int height, bool fullscreen_){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return false; }

	if (TTF_Init() != 0){ return false; }

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	getPossibleResolutions();
	if (fullscreen_){
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN;
		fullscreen = fullscreen_;
		
		windowedWidth = 640; windowedHeight = 360;
		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fullWidth, fullHeight, flags);
	} else {
		flags = SDL_WINDOW_SHOWN;
		fullscreen = fullscreen_;
		windowedWidth = width; windowedHeight = height;
		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowedWidth, windowedHeight, flags);
	}

	if (window == nullptr) { return false; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) { return false; }

	return true;
}

void GraphicsEngine::setFullscreen(bool fs){
	if (!fs){
		fullscreen = false;
		Settings::instance().setSetting("fullscreen", "false");
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		SDL_SetWindowSize(window, windowedWidth, windowedHeight);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}	else {
		fullscreen = true;
		Settings::instance().setSetting("fullscreen", "true");
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_GetWindowSize(window, &fullWidth, &fullHeight);
	}
	Settings::instance().saveSettings();
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

SDL_Texture * GraphicsEngine::getTextTexture(const char* p, TTF_Font* f, SDL_Color c){
	SDL_Surface * surf = TTF_RenderText_Blended(f, p, c);
	texture = makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

TTF_Font * GraphicsEngine::getFont(){
	if (font == nullptr)
		font = TTF_OpenFont("text.TTF", 64);

	return font;
}

SDL_Rect GraphicsEngine::setRectToMiddle(int sizeW_, int sizeH_){
	int h = getWindowHeight();
	int w = getWindowWidth();
	return{ ((w / 2) - sizeW_ / 2), ((h / 2) - sizeH_ / 2), sizeW_, sizeH_ };
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

void GraphicsEngine::drawRect(SDL_Rect rect, SDL_Color c){
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
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