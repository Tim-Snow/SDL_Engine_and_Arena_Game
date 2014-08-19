#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "State.h"

class PlayState : public State{
public:
	void init(Game* g);
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);
	
	PlayState();
};

class PauseState : public State{
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