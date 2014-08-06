#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	state.push_back(TITLE_SCREEN);
	menuWait = 0;
	loadResources();
}

void Game::loadResources(){
	fontColour = { 255, 255, 255, 255 };
	font = TTF_OpenFont("text.TTF", 64);

	resources[MENU_BG] = getTexture("red.bmp");
	resources[1] = getTextTexture("Title Screen");
	resources[2] = getTextTexture("Main Menu");
	resources[3] = getTextTexture("Play");
	resources[4] = getTextTexture("Pause");

	/*
	double w = gfx->getWindowWidth() / 2;
	double h = gfx->getWindowHeight() / 2;
	textObject.addTextureToObject(resources[0]);
	GameObject a{ 100, 100, 150, 100, false, true };
	gameObjects.push_back(a);
	*/
}

SDL_Texture * Game::getTextTexture(const char* c){
	SDL_Surface * surf = TTF_RenderText_Blended(font, c, fontColour);
	texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

SDL_Texture * Game::getTexture(char* p){
	SDL_Surface * surf = res->loadBMP(p);
	texture = gfx->makeTextureFromSurf(surf);
	SDL_FreeSurface(surf);
	return texture;
}

SDL_Texture * Game::getResource(int i){
	return resources[i];
}

void Game::update(double d){
	if (menuWait > 0){
		menuWait = menuWait - d;
	}
	else if (menuWait < 0){
		menuWait = 0;
	}

	if (input->isPressed(SDLK_w) && menuWait == 0){
		gfx->toggleFullscreen();
		menuWait = 500;
	}

	switch (state.back()){
	case TITLE_SCREEN:
		if (input->isAnyKeyPressed() && menuWait == 0){
			state.push_back(MAIN_MENU);
			menuWait = 500;
		}
		break;
	case MAIN_MENU:
		if (input->isPressed(SDLK_SPACE) && menuWait == 0){
			state.push_back(PLAY);
			menuWait = 500;
		}
		break;
	case PLAY:
		if (input->isPressed(SDLK_ESCAPE) && menuWait == 0){
			std::cout << "a" << std::endl;
			state.push_back(PAUSE);
			menuWait = 500;
		}
	case PAUSE:
		if (input->isPressed(SDLK_ESCAPE) && menuWait == 0){
			state.pop_back();
			menuWait = 500;
		}
		break;
	default:
		break;
	}	
}

void Game::draw(){
	/*-- FIRST PART OF DRAW MUST CLEAR DISPLAY --*/
		gfx->clearDisplay();
	/*-------------------------------------------*/

	if (state.back() == TITLE_SCREEN){
		gfx->drawFullBG(resources[MENU_BG]);
		gfx->draw(resources[1], { 200, 200, 200, 200 });
	}
	if (state.back() == MAIN_MENU){
		gfx->draw(resources[2], { 200, 200, 200, 200 });
	}
	if (state.back() == PLAY){
		gfx->draw(resources[3], { 200, 200, 200, 200 });
	}
	if (state.back() == PAUSE){
		gfx->draw(resources[4], { 200, 200, 200, 200 });
	}

	/*-- LAST PART OF DRAW MUST UPDATE DISPLAY --*/
		gfx->updateDisplay();
	/*-------------------------------------------*/
}

Game::~Game(){
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	core.exit();
}