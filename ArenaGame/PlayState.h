#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "../Engine/MenuSystem.h"

class PlayState : public State{
public:
	void init(Game* g);
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);
	
	PlayState();
	State * pauseState;
};

class PauseState : public MenuSystem{
public:
	void init(Game* g);
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);

	PauseState();
private:
	SDL_Texture * pauseMessage;
};
#endif /* defined (_PLAYSTATE_H_)*/