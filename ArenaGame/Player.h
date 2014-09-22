#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

enum playerClasses { WARRIOR, FIGHTER, WIZARD, TACTICIAN, NO_CLASS };

class Player : public GameObject{
public:
	Player();

	void update(){}
	void draw(std::shared_ptr<GraphicsEngine> g);
	void draw(std::shared_ptr<GraphicsEngine> g, SDL_Rect pos);

	void setClass(playerClasses p);
	playerClasses getClass()		{ return playerClass;	}
private:
	int				currentStep;
	SDL_Rect		pos;
	Sprite			playerBody;
	Sprite			playerArms;
	Sprite			playerLegsRunning[3];
	Sprite			playerWeapon;
	playerClasses playerClass;
};

#endif /* defined (_PLAYER_H_) */