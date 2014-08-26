#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "../Engine/MenuSystem.h"

class PlayState : public State{
public:
	void init();
	void clean();

	void handleEvent();
	void draw();
	void update(double d);
		
	PlayState();
	State * pauseState;
};

class PauseState : public MenuSystem{
public:
	void init();
	void clean();

	void handleEvent();
	void draw();
	void update(double d);

	PauseState();
private:
	SDL_Texture * pauseMessage;
};
#endif /* defined (_PLAYSTATE_H_)*/