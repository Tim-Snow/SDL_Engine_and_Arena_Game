#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/InputManager.h"
#include "GameObject.h"

enum playerClasses { WARRIOR, FIGHTER, WIZARD, TACTICIAN, NO_CLASS };
enum playerStates  { PLAYER_IDLE, PLAYER_WALKING, PLAYER_RUNNING, PLAYER_DUCKING, PLAYER_DEATH };

class Player : public GameObject{
public:
	Player();

	void handleEvent(std::shared_ptr<InputManager> i);
	void update();
	void draw(std::shared_ptr<GraphicsEngine> g);
	void draw(std::shared_ptr<GraphicsEngine> g, SDL_Rect pos);

	void			jump();
	void			isFlipped(bool b);
	void			setClass(playerClasses p);
	bool			inAir()						{ return air;				}
	void			setAir(bool b)				{ air = b;					}
	void			setState(playerStates s)	{ playerState  = s;			}
	void			setControllerID(int i)		{ controllerId = i;			}
	
	int				getControllerID()			{ return controllerId;		}
	playerStates	getState()					{ return playerState;		}
	playerClasses	getClass()					{ return playerClass;		}
private:
	bool				air;
	SDL_Rect			mainPos, legPos, armPos, weapPos;
	int					controllerId, cStep;
	Sprite				playerBody;
	Sprite				playerDucking;			Sprite			playerArms;
	Sprite				playerLegsRunning[3];	Sprite			playerWeapon;
	playerClasses		playerClass;			playerStates	playerState;
};

#endif /* defined (_PLAYER_H_) */