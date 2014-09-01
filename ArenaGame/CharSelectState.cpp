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
	
	playerQuarter player1(player1Quad, input->getController(0));
	playerQuarter player2(player2Quad, input->getController(1));
	playerQuarter player3(player3Quad, input->getController(2));
	playerQuarter player4(player4Quad, input->getController(3));
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	title.setTexture(ResourceLoader::getResource("charSelText")).setPosition({ gfx->getWindowWidth() / 2 - 100, 10, 200, 75 });

	addItem(&title);
}

void CharSelectState::handleEvent(){
	menuInput = NONE;

	for (int i = 0; i < players.size(); i++){
		switch (players[i].thisPlayerState){
		case EDITING:
			if (input->isControllerPressed(i, SDL_CONTROLLER_BUTTON_A)){
				players[i].status = ResourceLoader::getResource("readyText");
				players[i].thisPlayerState = READY;
				readyPlayers += 1;
			}
			if (input->isControllerPressed(i, SDL_CONTROLLER_BUTTON_B)){
				players[i].thisPlayerState = NOT_PLAYING;
			}
			break;
		case READY:
			if (readyPlayers > 1 && (input->isPressed(SDLK_SPACE) || input->isControllerPressed(i, SDL_CONTROLLER_BUTTON_START))){
					menuInput = ACCEPT;
			}
			if (input->isControllerPressed(i, SDL_CONTROLLER_BUTTON_B)){
				players[i].status = ResourceLoader::getResource("pressButtonText");
				players[i].thisPlayerState = EDITING;
				readyPlayers -= 1;
			}
			break;
		case NOT_PLAYING:
			if (input->isControllerPressed(i, SDL_CONTROLLER_BUTTON_A)){
				players[i].thisPlayerState = EDITING;
			}
			if (input->isControllerPressed(i, SDL_CONTROLLER_BUTTON_B)){
				menuInput = BACK;
			}
			break;
		default:
			break;
		}
	}

	if (input->isPressed(SDLK_ESCAPE)){
		menuInput = BACK;
	}
}

void CharSelectState::update(double d){
	if (menuInput == ACCEPT)
		goPlay();

	if (menuInput == BACK)
		StateManager::instance().popState();
}


void CharSelectState::draw(){
	gfx->drawFullBG(background);
	
	for (auto p : players){
		gfx->draw(p.background, p.pos);

		if (p.thisPlayerState == NOT_PLAYING || p.thisPlayerState == READY){
			gfx->draw(p.status, p.statusPos);
		}

		if (p.thisPlayerState == EDITING){
			for (auto b : p.buttons){
				b.draw(gfx, p.selectedButton);
			}
		}
	}
	for (auto i : items){
		i->draw(gfx);
	}

}