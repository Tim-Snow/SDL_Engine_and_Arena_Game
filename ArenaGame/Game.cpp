#include "Game.h"

Game::Game(){
	gfx = std::shared_ptr<GraphicsEngine>(core.gfxEng);
	input = std::shared_ptr<InputManager>(core.theInput);
	loadResources();
	StateManager::instance().setup(gfx, input);
	StateManager::instance().pushState(&titleScreen);
}

void Game::loadResources(){
	SDL_Color fontColour = { 30, 100, 205, 255 };
	SDL_Surface * surf = nullptr;

	surf = ResourceLoader::loadImage("res/titleBackground.png");
	ResourceLoader::addResource("titleBG", gfx->makeTextureFromSurf(surf));

	surf = ResourceLoader::loadImage("res/menuBackground.png");
	ResourceLoader::addResource("menuBG", gfx->makeTextureFromSurf(surf));

	surf = ResourceLoader::loadImage("res/spritesheet2.png");
	ResourceLoader::addResource("spritesheet2", gfx->makeTextureFromSurf(surf));

	surf = ResourceLoader::loadImage("res/level.png");
	ResourceLoader::addResource("levelBG", gfx->makeTextureFromSurf(surf));

	surf = ResourceLoader::loadImage("res/daysky.png");
	ResourceLoader::addResource("dayBG", gfx->makeTextureFromSurf(surf));

	surf = ResourceLoader::loadImage("res/nightsky.png");
	ResourceLoader::addResource("nightBG", gfx->makeTextureFromSurf(surf));

	ResourceLoader::addResource("anykeyText",		gfx->getTextTexture("Press any key to continue..!", gfx->getFont(), fontColour));
	ResourceLoader::addResource("titleText",		gfx->getTextTexture("Arena Game",					gfx->getFont(), fontColour));
	ResourceLoader::addResource("playText",			gfx->getTextTexture("Play",							gfx->getFont(), fontColour));
	ResourceLoader::addResource("libraryText",		gfx->getTextTexture("Library",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("optionsText",		gfx->getTextTexture("Options",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("exitText",			gfx->getTextTexture("Exit",							gfx->getFont(), fontColour));
	ResourceLoader::addResource("charSelText",		gfx->getTextTexture("Character Select",				gfx->getFont(), fontColour));
	ResourceLoader::addResource("pressStartText",	gfx->getTextTexture("Press Start to play!",			gfx->getFont(), fontColour));
	ResourceLoader::addResource("pressButtonText",	gfx->getTextTexture("Press A to join!",				gfx->getFont(), fontColour));
	ResourceLoader::addResource("readyText",		gfx->getTextTexture("Ready!",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("noConnectText",	gfx->getTextTexture("Controller not found",			gfx->getFont(), fontColour));
	ResourceLoader::addResource("talentText",		gfx->getTextTexture("Talents",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("classText",		gfx->getTextTexture("Class",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("readyText",		gfx->getTextTexture("Ready",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("saveText",			gfx->getTextTexture("Save",							gfx->getFont(), fontColour));
	ResourceLoader::addResource("loadText",			gfx->getTextTexture("Load",							gfx->getFont(), fontColour));
	ResourceLoader::addResource("fullscreenText",	gfx->getTextTexture("Fullscreen",					gfx->getFont(), fontColour));
	ResourceLoader::addResource("resolutionText",	gfx->getTextTexture("Resolution",					gfx->getFont(), fontColour));
	ResourceLoader::addResource("acceptText",		gfx->getTextTexture("Accept",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("backText",			gfx->getTextTexture("Back",							gfx->getFont(), fontColour));

	//char select player quadrant border
	//characters and items from spritesheet
	//level sprite sheet
	SDL_FreeSurface(surf);
}

void Game::handleEvent(){
	input->pollEvent();
	StateManager::instance().getState()->handleEvent();
}

void Game::update(double d){
	StateManager::instance().getState()->update(d);
}

void Game::draw(){
		gfx->clearDisplay();
		StateManager::instance().getState()->draw();
		gfx->updateDisplay();
}

Game::~Game(){
	StateManager::instance().clean();
	ResourceLoader::clean();
	SDL_DestroyTexture(texture);
	core.exit();
}