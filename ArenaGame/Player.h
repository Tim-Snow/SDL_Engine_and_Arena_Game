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

	bool collidesWith(SDL_RectF obj){
		return !(obj.x > mainPos.x + mainPos.w
			|| obj.x + obj.w < mainPos.x
			|| obj.y > mainPos.y + mainPos.h
			|| obj.y + obj.h < mainPos.y) ||

			!(obj.x > legPos.x + legPos.w
			|| obj.x + obj.w < legPos.x
			|| obj.y > legPos.y + legPos.h
			|| obj.y + obj.h < legPos.y);
	}
	void			jump();
	void			isFlipped(bool b);
	void			setClass(playerClasses p);
	void			setAir(bool b)				{ air = b;					}
	void			setState(playerStates s)	{ playerState  = s;			}
	void			setControllerID(int i)		{ controllerId = i;			}

	bool			inAir()						{ return air;				}	
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