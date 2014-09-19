#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

enum playerClasses { WARRIOR, FIGHTER, WIZARD, TACTICIAN };

class Player : public GameObject{
public:
	Player(){}

	void update(){}
	void draw();

	void setClass(playerClasses p)	{ playerClass = p;		}
	playerClasses getClass()		{ return playerClass;	}
private:
	playerClasses playerClass;
};

#endif /* defined (_PLAYER_H_) */