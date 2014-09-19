#include "CharSelectState.h"

void goPlay(){
	PlayState * play = new PlayState();
	StateManager::instance().pushState(play);
}

void CharSelectState::init(){
	setBackgroundImage(ResourceLoader::getResource("titleBG"));
	title.setTexture(ResourceLoader::getResource("charSelText")).setPosition({ gfx->getWindowWidth() / 2 - 100, 10, 200, 75 });
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
	addItem(&title);
}

void CharSelectState::handleEvent(){
	menuInput = NONE;

	for (auto p : players){
		p->handleEvent(input);
		if ((p->getInput() == BACK) && (p->getState() == NOT_PLAYING))
			menuInput = BACK;
	}

	if (input->isControllerPressed(SDL_CONTROLLER_BUTTON_START) && readyPlayers >= 1){
		goPlay();

		for (auto p : players){
			p->setState(EDITING);
		}
	}

	if (input->isPressed(SDLK_ESCAPE))
		menuInput = BACK;
}

void CharSelectState::update(double d){
	readyPlayers = 0;
	for (auto p : players){
		p->update(d);
		if (p->getState() == READY)
			readyPlayers++;
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

	if (readyPlayers>=1){
		gfx->draw(ResourceLoader::getResource("pressStartText"), { gfx->getWindowWidth() / 2 - 200, gfx->getWindowHeight() / 2, 400, 150 });
	}
}

playerQuarter::playerQuarter(const int i, SDL_Rect p) : id(i), pos(p), selectedButton(0), playerInput(NONE), thisPlayerState(NOT_PLAYING), bg(ResourceLoader::getResource("menuBG")){
	player.setClass(WARRIOR);
	theChar = ResourceLoader::getResource("spritesheet");
	//for sub menu position
	menuPos.x = pos.x + 20;	menuPos.y = pos.y + 40; menuPos.w = pos.w - 40;	menuPos.h = pos.h / 3;
	SDL_Rect itemPos = { menuPos.x + 10, menuPos.y +15, menuPos.w - 20, (menuPos.h - 20)/5 };

	//Init for the class select sub menu
	charClass.setTexture(ResourceLoader::getResource("menuBG")).setPosition(menuPos);
	warrior.setTexture(ResourceLoader::getResource("warriorText")).setID(0).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.y += (menuPos.h - 20) / 4;
	fighter.setTexture(ResourceLoader::getResource("fighterText")).setID(1).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.y += (menuPos.h - 20) / 4;
	wizard.setTexture(ResourceLoader::getResource("wizardText")).setID(2).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.y += (menuPos.h - 20) / 4;
	tactician.setTexture(ResourceLoader::getResource("tacticianText")).setID(3).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	charClass.addButton(&warrior);
	charClass.addButton(&fighter);
	charClass.addButton(&wizard);
	charClass.addButton(&tactician);

	//Init for the skill select sub menu
	charSkills.setTexture(ResourceLoader::getResource("menuBG")).setPosition(menuPos);

	//Init for the talent select sub menu
	charTalents.setTexture(ResourceLoader::getResource("menuBG")).setPosition(menuPos);

	itemPos = { p.x + 20, p.y + 20, p.w - 40, p.h / 10 };
	ready.setTexture(ResourceLoader::getResource("readyText")).setPosition(itemPos);
	pressToJoin.setTexture(ResourceLoader::getResource("pressButtonText")).setPosition(itemPos);
	noConnect.setTexture(ResourceLoader::getResource("noConnectText")).setPosition(itemPos);

	itemPos = { pos.x+20, (pos.y + pos.h - 160), (pos.w / 2) - 30, 40};
	cClass.setTexture(ResourceLoader::getResource("classText")).setID(0).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.x += pos.w / 2 -10;
	talents.setTexture(ResourceLoader::getResource("talentText")).setID(1).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.y -= 60; itemPos.x -= pos.w / 2 - 20; itemPos.w += itemPos.w;
	curClass.setTexture(ResourceLoader::getResource("warriorText")).setPosition(itemPos);

	itemPos = { p.x + 20, p.y + pos.h - 100, p.w - 40, 40 };
	accept.setTexture(ResourceLoader::getResource("acceptText")).setID(2).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.w = 60; itemPos.y += 60;
	load.setTexture(ResourceLoader::getResource("loadText")).setID(3).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.x += 75;
	save.setTexture(ResourceLoader::getResource("saveText")).setID(4).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
	itemPos.x += 75;
	back.setTexture(ResourceLoader::getResource("backText")).setID(5).setPosition(itemPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });

	buttons.push_back(&accept);
	buttons.push_back(&cClass);
	buttons.push_back(&talents);
	buttons.push_back(&back);
	buttons.push_back(&load);
	buttons.push_back(&save);
}

void playerQuarter::handleEvent(std::shared_ptr<InputManager> i){
	if (i->isControllerAvailble(id)){
		if (thisPlayerState == NO_CONTROLLER)
			thisPlayerState = NOT_PLAYING;

		playerInput = NONE;
		if (i->isControllerPressed(SDL_CONTROLLER_BUTTON_DPAD_UP, id) || (i->isLeftJoystickMoved(id) == J_UP) || (i->isLeftJoystickMoved(id) == J_LEFT))
			playerInput = UP;

		if (i->isControllerPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN, id) || (i->isLeftJoystickMoved(id) == J_RIGHT) || (i->isLeftJoystickMoved(id) == J_DOWN))
			playerInput = DOWN;

		if (thisPlayerState == EDITING && i->isControllerPressed(SDL_CONTROLLER_BUTTON_START, id))
			thisPlayerState = READY;

		if (i->isControllerPressed(SDL_CONTROLLER_BUTTON_B, id))
			playerInput = BACK;

		if (i->isControllerPressed(SDL_CONTROLLER_BUTTON_A, id))
			playerInput = ACCEPT;
	} else {
		thisPlayerState = NO_CONTROLLER;
	}
}

void playerQuarter::update(double d){
	switch (thisPlayerState){
	case READY:		if (playerInput == BACK)	thisPlayerState = EDITING;		break;
	case NOT_PLAYING:
		if (playerInput == ACCEPT){
			selectedButton = 0;
			thisPlayerState = EDITING;
		}
		if (playerInput == BACK)
			playerInput = BACK;
		break;
	case EDITING:	
		if (playerInput == UP){
			if (selectedButton != 0)
				selectedButton--;
		}
		if (playerInput == DOWN){
			if (selectedButton != buttons.size()-1)
				selectedButton++;
		}
		if (playerInput == BACK)
			thisPlayerState = NOT_PLAYING;
		
		if (playerInput == ACCEPT){
			switch (selectedButton){
			case 0:	thisPlayerState = CLASS_SELECT;	 break;
			//case 1:	thisPlayerState = TALENT_SELECT; break;
			case 2: thisPlayerState = READY; 		 break;
			case 3:									 break;
			case 4:									 break;
			case 5: thisPlayerState = NOT_PLAYING;	 break;
			default:
				break;
			}
		}
		break;

	case CLASS_SELECT:
		if (playerInput == UP)
			charClass--;
		if (playerInput == DOWN)
			charClass++;
		if (playerInput == BACK)
			thisPlayerState = EDITING;
		if (playerInput == ACCEPT){
			player.setClass((playerClasses)charClass.getSelectedButton());
			thisPlayerState = EDITING;
			switch (player.getClass()){
			case WARRIOR:	curClass.setTexture(ResourceLoader::getResource("warriorText"));	break;
			case FIGHTER:	curClass.setTexture(ResourceLoader::getResource("fighterText"));	break;
			case WIZARD:	curClass.setTexture(ResourceLoader::getResource("wizardText"));		break;
			case TACTICIAN:	curClass.setTexture(ResourceLoader::getResource("tacticianText"));	break;
			default:
				break;
			}
		}
	case TALENT_SELECT:
	case SKILL_SELECT:		
		break;
	case NO_CONTROLLER:
	default:
		break;
	}
}

void playerQuarter::draw(std::shared_ptr<GraphicsEngine> g){
	g->draw(bg, pos);
	
	if (thisPlayerState != NOT_PLAYING && thisPlayerState != NO_CONTROLLER){
		curClass.draw(g);
		g->drawFromSpritesheet(theChar, { 0, 960, 128, 128 }, { pos.x + 20, pos.y + 120, pos.w - 40, pos.w - 40 });
		g->drawFromSpritesheet(theChar, { 64, 1088, 128, 64 }, { pos.x + 90, pos.y + 200, 128, 64 });
		for (auto b : buttons){
			b->draw(g, selectedButton);
		}
	}

	switch (thisPlayerState){
	case NOT_PLAYING:		pressToJoin.draw(g);	break;
	case NO_CONTROLLER:		noConnect.draw(g);		break;
	case READY:				ready.draw(g);			break;
	case CLASS_SELECT:		charClass.draw(g, charClass.getSelectedButton());	break;
	case TALENT_SELECT:
	case SKILL_SELECT:		break;
	default:				break;
	}
}