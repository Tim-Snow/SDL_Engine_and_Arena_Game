#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "State.h"

class PlayState : public State{
public:
	static PlayState& instance()
	{
		static PlayState *instance = new PlayState();
		return *instance;
	}

	void init();
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);
protected:
private:
	PlayState();
};

#endif /* defined (_PLAYSTATE_H_)*/