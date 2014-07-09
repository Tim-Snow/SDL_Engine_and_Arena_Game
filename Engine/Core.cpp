#include "Core.h"

void Core::setTitle(string s){
	name = s;
}

//Creates the window for the application, initializing SDL, returns 0 if operation was successful
bool Core::initialize() {

	gameSettings.updateSettings();
	running = true;

	//read screen sizes from settings map set by ini file
	string w = gameSettings.settings.at("screenWidth");
	width = atoi(w.c_str());
	string h = gameSettings.settings.at("screenHeight");
	height = atoi(h.c_str());

	//minimum resolution of 640x480
	if (width < 640){ width = 640; gameSettings.settings["screenWidth"] = width; }
	if (height < 480){ height = 480; gameSettings.settings["screenHeight"] = height; }

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	SDL_Window *window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		return false;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	return true;
}

void Core::mainLoop(){
	while (running){

	}
}
/*
void getInput(){
}

void update(){

}

void draw(){

}*/