#include "Player.h"

Player::Player() : GameObject(256, 256, true, true, true), playerState(PLAYER_IDLE), playerClass(NO_CLASS), controllerId(0), cStep(0), air(false){
	playerBody			 = ResourceLoader::getSprite("Player");
	playerArms			 = ResourceLoader::getSprite("PlayerArms");
	playerDucking        = ResourceLoader::getSprite("PlayerDucking");
	playerLegsRunning[0] = ResourceLoader::getSprite("PlayerLegs1");
	playerLegsRunning[1] = ResourceLoader::getSprite("PlayerLegs2");
	playerLegsRunning[2] = ResourceLoader::getSprite("PlayerLegs3");

	mainPos = armPos = legPos = { screenPos.x, screenPos.y, fwidth, fheight };
	weapPos = { screenPos.x + fwidth / 3, screenPos.y, fwidth, fheight };
}

void Player::isFlipped(bool b){ 
	if (flipped != b){	flipped = b;
		if (flipped){
			playerDucking.setFlip(SDL_FLIP_NONE);
			playerBody.setFlip(SDL_FLIP_NONE);
			playerArms.setFlip(SDL_FLIP_NONE);
			playerLegsRunning[0].setFlip(SDL_FLIP_NONE);
			playerLegsRunning[1].setFlip(SDL_FLIP_NONE);
			playerLegsRunning[2].setFlip(SDL_FLIP_NONE);
			playerWeapon.setFlip(SDL_FLIP_NONE);
		} else {
			playerDucking.setFlip(SDL_FLIP_HORIZONTAL);
			playerBody.setFlip(SDL_FLIP_HORIZONTAL);
			playerArms.setFlip(SDL_FLIP_HORIZONTAL);
			playerLegsRunning[0].setFlip(SDL_FLIP_HORIZONTAL);
			playerLegsRunning[1].setFlip(SDL_FLIP_HORIZONTAL);
			playerLegsRunning[2].setFlip(SDL_FLIP_HORIZONTAL);
			playerWeapon.setFlip(SDL_FLIP_HORIZONTAL);
		}
	}
}

void Player::jump(){
	velocity.y = -4.00;
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

void Player::handleEvent(std::shared_ptr<InputManager> i){
	if (i->isControllerPressed(SDL_CONTROLLER_BUTTON_A, controllerId))
		jump();

	if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTX) <= -8000){
		isFlipped(false);
		setState(PLAYER_WALKING);
		if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTX) <= -24000)
			setState(PLAYER_RUNNING);
	}
	else if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTX) >= 8000){
		isFlipped(true);
		setState(PLAYER_WALKING);
		if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTX) >= 24000)
			setState(PLAYER_RUNNING);
	} else{ setState(PLAYER_IDLE); }

	if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTY) >= 20000){
		int horizVal = 0;
		if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTX) < 0){
			horizVal = i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTX);
			horizVal = -horizVal;	//if left stick is negative (moved to left), make the number positive so it can be checked against +y axis
		}
		if (i->getControllerAxisValue(controllerId, SDL_CONTROLLER_AXIS_LEFTY) > horizVal)
			setState(PLAYER_DUCKING);
	}
}

void Player::update(){
	++cStep;
	if (velocity.x != 0.00){
		float slowSpeed = 0.00;
		if (playerState == PLAYER_IDLE)		slowSpeed = 0.10;
		if (playerState == PLAYER_DUCKING)	slowSpeed = 0.05;

		if		(velocity.x >  0.10)	{ velocity.x -= slowSpeed; }
		else if (velocity.x < -0.10)	{ velocity.x += slowSpeed; }
		else	 velocity.x = 0.00;
	}

	if (air){
		velocity.y += 0.10;
	} else if (velocity.y > 0.00){ //if not in air and yVel is falling, stop
		velocity.y = 0.00;
	}

	if (flipped){
		if (playerState == PLAYER_WALKING){
			if (velocity.x < 1.0)	velocity.x = 1.0;
		}
		if (playerState == PLAYER_RUNNING){
			if (velocity.x < 5.0)	velocity.x += 0.1;
			++cStep;
		}
	} else {
		if (playerState == PLAYER_WALKING){
			if (velocity.x > -1.0)	velocity.x = -1.0;
		}
		if (playerState == PLAYER_RUNNING){
			if (velocity.x > -5.0)	velocity.x -= 0.1;
			++cStep;
		}
	}

	if (playerState == PLAYER_IDLE || playerState == PLAYER_DUCKING || cStep >= 60) cStep = 0; 

	legPos = mainPos = armPos = { screenPos.x, screenPos.y, fwidth, fheight };
	if (flipped) weapPos = { screenPos.x + fwidth / 3, screenPos.y, fwidth, fheight };
	else weapPos = { screenPos.x - fwidth / 3, screenPos.y, fwidth, fheight };
}

void Player::draw(std::shared_ptr<GraphicsEngine> g, SDL_Rect pos){
	g->drawFromSpritesheet(playerLegsRunning[0], { pos.x, pos.y, width, height });
	g->drawFromSpritesheet(playerBody, { pos.x, pos.y, width, height });
	if (playerClass == FIGHTER)	g->drawFromSpritesheet(playerArms, { pos.x, pos.y, width, height });
	g->drawFromSpritesheet(playerWeapon, { pos.x + width / 3, pos.y, width, height });
	if (playerClass != FIGHTER)	g->drawFromSpritesheet(playerArms, { pos.x, pos.y, width, height });
}

void Player::draw(std::shared_ptr<GraphicsEngine> g){
	if (cStep < 15)
		g->drawFromSpritesheet(playerLegsRunning[0],	legPos);
	if (cStep < 30 && cStep >= 15)
		g->drawFromSpritesheet(playerLegsRunning[1],	legPos);
	if (cStep < 45 && cStep >= 30)
		g->drawFromSpritesheet(playerLegsRunning[2],	legPos);
	if (cStep < 60 && cStep >= 45)
		g->drawFromSpritesheet(playerLegsRunning[1],	legPos);

	//BODY
	if (playerState != PLAYER_DUCKING){
		g->drawFromSpritesheet(playerBody,				mainPos);

	//ARMS + WEAPON
	if (playerClass == FIGHTER) //arms behind fist
		g->drawFromSpritesheet(playerArms,				armPos);

	g->drawFromSpritesheet(playerWeapon,				weapPos);

	if (playerClass != FIGHTER)
		g->drawFromSpritesheet(playerArms, armPos);
	} else {
		g->drawFromSpritesheet(playerDucking,			mainPos);
	}


}