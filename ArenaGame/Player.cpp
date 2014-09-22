#include "Player.h"
Player::Player() : currentStep(0){
	pos.h = 256;	pos.w = 256;
	playerBody = ResourceLoader::getSprite("Player");
	playerArms = ResourceLoader::getSprite("PlayerArms");

	playerLegsRunning[0] = ResourceLoader::getSprite("PlayerLegs1");
	playerLegsRunning[1] = ResourceLoader::getSprite("PlayerLegs2");
	playerLegsRunning[2] = ResourceLoader::getSprite("PlayerLegs3");
}

void Player::setClass(playerClasses c){
	playerClass = c;

	switch (playerClass){
		case WARRIOR:	playerWeapon = ResourceLoader::getSprite("Sword");	break;
		case FIGHTER:	playerWeapon = ResourceLoader::getSprite("Fist");	break;
		case WIZARD:	playerWeapon = ResourceLoader::getSprite("Wand");	break;		
		case TACTICIAN:	playerWeapon = ResourceLoader::getSprite("Gun");	break;
		default:		break;
	}
}

void Player::draw(std::shared_ptr<GraphicsEngine> g, SDL_Rect pos){
	//LEGS + WALKING
	if (currentStep < 15)
		g->drawFromSpritesheet(playerLegsRunning[0], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });
	
	if (currentStep < 30 && currentStep >= 15)
		g->drawFromSpritesheet(playerLegsRunning[1], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });
	
	if (currentStep < 45 && currentStep >= 30)
		g->drawFromSpritesheet(playerLegsRunning[2], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });
	
	if (currentStep < 60 && currentStep >= 45)
		g->drawFromSpritesheet(playerLegsRunning[1], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });

	currentStep++;		if (currentStep == 60)		currentStep = 0;

	//BODY
	g->drawFromSpritesheet(playerBody, { pos.x, pos.y, pos.w - 40, pos.w - 40 });

	//ARMS + WEAPON
	if (playerClass == FIGHTER) //arms behind fist
		g->drawFromSpritesheet(playerArms, { pos.x - 5, pos.y + 15, pos.w - 40, pos.w - 40 });
	
	g->drawFromSpritesheet(playerWeapon, { pos.x + 70, pos.y + 10, 256, 256 });

	if (playerClass != FIGHTER)
		g->drawFromSpritesheet(playerArms, { pos.x - 5, pos.y + 15, pos.w - 40, pos.w - 40 });
}

void Player::draw(std::shared_ptr<GraphicsEngine> g){
	//LEGS + WALKING
	if (currentStep < 15)
		g->drawFromSpritesheet(playerLegsRunning[0], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });

	if (currentStep < 30 && currentStep >= 15)
		g->drawFromSpritesheet(playerLegsRunning[1], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });

	if (currentStep < 45 && currentStep >= 30)
		g->drawFromSpritesheet(playerLegsRunning[2], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });

	if (currentStep < 60 && currentStep >= 45)
		g->drawFromSpritesheet(playerLegsRunning[1], { pos.x, pos.y + 185, pos.w - 40, pos.w - 40 });

	currentStep++;		if (currentStep == 60)		currentStep = 0;

	//BODY
	g->drawFromSpritesheet(playerBody, { pos.x, pos.y, pos.w - 40, pos.w - 40 });

	//ARMS + WEAPON
	if (playerClass == FIGHTER) //arms behind fist
		g->drawFromSpritesheet(playerArms, { pos.x - 5, pos.y + 15, pos.w - 40, pos.w - 40 });

	g->drawFromSpritesheet(playerWeapon, { pos.x + 70, pos.y + 10, 256, 256 });
	if (playerClass != FIGHTER)
		g->drawFromSpritesheet(playerArms, { pos.x - 5, pos.y + 15, pos.w - 40, pos.w - 40 });
}