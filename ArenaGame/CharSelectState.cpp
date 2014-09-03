#include "CharSelectState.h"

void goPlay(){
	PlayState * play = new PlayState();
	StateManager::instance().pushState(play);
}

void CharSelectState::init(){
	setBackgroundImage(ResourceLoader::getResource("titleBG"));
	setBorderColour({ 60, 60, 60, 255 });
	setSelBorderColour({ 150, 150, 150, 255 });
	setItemBgColour({ 200, 200, 200, 255 });

	SDL_Rect player1Quad = { (gfx->getWindowWidth() / 2) - (((gfx->getWindowWidth()/5)+10)*2), (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	SDL_Rect player2Quad = { (gfx->getWindowWidth() / 2) - ((gfx->getWindowWidth() / 5 ) + 5), (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	SDL_Rect player3Quad = { (gfx->getWindowWidth() / 2) + 5								 , (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };
	SDL_Rect player4Quad = { (gfx->getWindowWidth() / 2) + ((gfx->getWindowWidth() / 5) + 20), (gfx->getWindowHeight() / 20)*3	, gfx->getWindowWidth() / 5, (gfx->getWindowHeight() / 10) * 8 };

	playerQuarter * player1 = new playerQuarter(0, player1Quad);
	playerQuarter * player2 = new playerQuarter(1, player2Quad);
	playerQuarter * player3 = new playerQuarter(2, player3Quad);
	playerQuarter * player4 = new playerQuarter(3, player4Quad);
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	title.setTexture(ResourceLoader::getResource("charSelText")).setPosition({ gfx->getWindowWidth() / 2 - 100, 10, 200, 75 });

	addItem(&title);
}

void CharSelectState::handleEvent(){
	menuInput = NONE;

	for (auto p : players){
		p->handleEvent(input);
		if (p->getInput() == BACK){
			menuInput = BACK;
		}
	}

	if (input->isControllerPressed(SDL_CONTROLLER_BUTTON_START) && readyPlayers > 1){
		goPlay();
	}

	if (input->isPressed(SDLK_ESCAPE)){
		menuInput = BACK;
	}
}

void CharSelectState::update(double d){
	readyPlayers = 0;
	for (auto p : players){
		p->update(d);
		if (p->isReady()){
			readyPlayers++;
		}
	}

	if (menuInput == BACK)
		StateManager::instance().popState();
}

void CharSelectState::draw(){
	gfx->drawFullBG(background);
	
	for (auto p : players){
		p->draw(gfx);
	}

	for (auto i : items){
		i->draw(gfx);
	}

	if (readyPlayers>1){
		gfx->draw(ResourceLoader::getResource("pressStartText"), { gfx->getWindowWidth() / 2 - 150, gfx->getWindowHeight() / 2, 300, 100 });
	}
}

playerQuarter::playerQuarter(int i, SDL_Rect p) : id(i), pos(p){
	selectedButton = 0;
	menuInput = NONE;
	thisPlayerState = NOT_PLAYING;
	bg = ResourceLoader::getResource("menuBG");

	SDL_Rect itemPos = { p.x + 20, p.y + 20, p.w - 40, 80 };
	ready.setTexture(ResourceLoader::getResource("readyText")).setPosition(itemPos);
	pressToJoin.setTexture(ResourceLoader::getResource("pressButtonText")).setPosition(itemPos);
	
	itemPos = { pos.x+20, (pos.y + pos.h - 160), (pos.w / 2) - 30, 40};

	charClass.setTexture(ResourceLoader::getResource("classText")).setID(0).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.x += pos.w / 2 -10;
	talents.setTexture(ResourceLoader::getResource("talentText")).setID(1).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	
	theChar = ResourceLoader::getResource("spritesheet2");
	
	itemPos = { p.x + 20, p.y + pos.h - 100, p.w - 40, 40 };
	accept.setTexture(ResourceLoader::getResource("acceptText")).setID(2).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.w = 60; itemPos.y += 60;
	load.setTexture(ResourceLoader::getResource("loadText")).setID(3).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.x += 75;
	save.setTexture(ResourceLoader::getResource("saveText")).setID(4).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.x += 75;
	back.setTexture(ResourceLoader::getResource("backText")).setID(5).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });

	buttons.push_back(&accept);
	buttons.push_back(&charClass);
	buttons.push_back(&talents);
	buttons.push_back(&back);
	buttons.push_back(&load);
	buttons.push_back(&save);
}

void playerQuarter::handleEvent(std::shared_ptr<InputManager> i){
	if (i->getController(id).inUse == true){
		switch (thisPlayerState){
		case EDITING:
			if (i->isControllerPressed(id, SDL_CONTROLLER_BUTTON_DPAD_UP) || (i->isLeftJoystickMoved(id) == J_UP) || (i->isLeftJoystickMoved(id) == J_LEFT)){
				selectedButton--;
			}
			if ((i->isLeftJoystickMoved(id) == J_RIGHT) || (i->isLeftJoystickMoved(id) == J_DOWN)){
				selectedButton++;
			}
			if (i->isControllerPressed(id, SDL_CONTROLLER_BUTTON_A)){
				thisPlayerState = READY;
			}
			if (i->isControllerPressed(id, SDL_CONTROLLER_BUTTON_B)){
				thisPlayerState = NOT_PLAYING;
			}
			break;
		case READY:
			if (i->isControllerPressed(id, SDL_CONTROLLER_BUTTON_B)){
				thisPlayerState = EDITING;
			}
			break;
		case NOT_PLAYING:
			pressToJoin.setTexture(ResourceLoader::getResource("pressButtonText"));
			if (i->isControllerPressed(id, SDL_CONTROLLER_BUTTON_A)){
				selectedButton = 0;
				thisPlayerState = EDITING;
			}
			if (i->isControllerPressed(id, SDL_CONTROLLER_BUTTON_B)){
				menuInput = BACK;
			}
			break;
		default:
			break;
		}
	}
	else {
		thisPlayerState = NOT_PLAYING;
		pressToJoin.setTexture(ResourceLoader::getResource("noConnectText"));
	}
}

void playerQuarter::update(double d){

}

void playerQuarter::draw(std::shared_ptr<GraphicsEngine> g){
	g->draw(bg, pos);

	if (thisPlayerState == NOT_PLAYING){
		pressToJoin.draw(g);
	}
	if (thisPlayerState == READY){
		ready.draw(g);
	}

	if (thisPlayerState != NOT_PLAYING){
		g->drawFromSpritesheet(theChar, { 0, 960, 128, 128 }, { pos.x + 20, pos.y + 120, 200, 200 });
		g->drawFromSpritesheet(theChar, { 64, 1088, 128, 64 }, { pos.x + 90, pos.y + 200, 128, 64 });
		for (auto b : buttons){
			b->draw(g, selectedButton);
		}
	}
}