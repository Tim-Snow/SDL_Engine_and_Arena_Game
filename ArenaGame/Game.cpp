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
	ResourceLoader::addResource("titleBG",		gfx->makeTextureFromSurf(surf));
	surf = ResourceLoader::loadImage("res/menuBackground.png");
	ResourceLoader::addResource("menuBG",		gfx->makeTextureFromSurf(surf));
	surf = ResourceLoader::loadImage("res/level.png");
	ResourceLoader::addResource("levelBG",		gfx->makeTextureFromSurf(surf));
	surf = ResourceLoader::loadImage("res/daysky.png");
	ResourceLoader::addResource("dayBG",		gfx->makeTextureFromSurf(surf));
	surf = ResourceLoader::loadImage("res/nightsky.png");
	ResourceLoader::addResource("nightBG",		gfx->makeTextureFromSurf(surf));
	surf = ResourceLoader::loadImage("res/spritesheet.png");
	ResourceLoader::addResource("spritesheet",	gfx->makeTextureFromSurf(surf));

	ResourceLoader::addSprite("MenuBG",			ResourceLoader::getResource("spritesheet"), { 256,  0,    256, 256 });
	ResourceLoader::addSprite("MenuBG2",		ResourceLoader::getResource("spritesheet"), { 0,    0,    256, 256 });
	ResourceLoader::addSprite("Player",			ResourceLoader::getResource("spritesheet"), { 0,    512,  256, 256 });
	ResourceLoader::addSprite("PlayerDucking",  ResourceLoader::getResource("spritesheet"), { 256,  256,  256, 256 });
	ResourceLoader::addSprite("PlayerLegs1",	ResourceLoader::getResource("spritesheet"), { 256,  512,  256, 256 });
	ResourceLoader::addSprite("PlayerLegs2",	ResourceLoader::getResource("spritesheet"), { 512,  512,  256, 256 });
	ResourceLoader::addSprite("PlayerLegs3",	ResourceLoader::getResource("spritesheet"), { 768,  512,  256, 256 });
	ResourceLoader::addSprite("PlayerArms",		ResourceLoader::getResource("spritesheet"), { 0,    256,  256, 256 });
	ResourceLoader::addSprite("Sword",			ResourceLoader::getResource("spritesheet"), { 256,  768,  256, 256 });
	ResourceLoader::addSprite("Fist",			ResourceLoader::getResource("spritesheet"), { 0,    768,  256, 256 });
	ResourceLoader::addSprite("Wand",			ResourceLoader::getResource("spritesheet"), { 512,  768,  256, 256 });
	ResourceLoader::addSprite("Gun",			ResourceLoader::getResource("spritesheet"), { 768,  768,  256, 256 });
	ResourceLoader::addSprite("Moon",			ResourceLoader::getResource("spritesheet"), { 1024, 512,  256, 256 });
	ResourceLoader::addSprite("Sun",			ResourceLoader::getResource("spritesheet"), { 1024, 768,  256, 256 });
	ResourceLoader::addSprite("Ground",			ResourceLoader::getResource("spritesheet"), { 0,    1024, 256, 256 });

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
	ResourceLoader::addResource("pickClassText",	gfx->getTextTexture("Select a class!",				gfx->getFont(), fontColour));
	ResourceLoader::addResource("warriorText",		gfx->getTextTexture("Warrior",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("wizardText",		gfx->getTextTexture("Wizard",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("fighterText",		gfx->getTextTexture("Fighter",						gfx->getFont(), fontColour));
	ResourceLoader::addResource("tacticianText",	gfx->getTextTexture("Tactician",					gfx->getFont(), fontColour));

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