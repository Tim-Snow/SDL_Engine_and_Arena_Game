#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"

class TitleState : public State{
public:
	static TitleState& instance()
	{
		static TitleState *instance = new TitleState();
		return *instance;
	}

	void init();
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);
protected:
private:
	TitleState();

	SDL_Texture * tsBackground;
};

#endif /* defined (_TITLESTATE_H_)*/