#ifndef STATE_H_
#define STATE_H_

enum MENU_COMMANDS { UP, DOWN, LEFT, RIGHT, ACCEPT, BACK, EXIT, NONE };

class Game;
#include <vector>
#include "../Engine/ResourceLoader.h"

class State{
public:
	virtual void init(Game* g) = 0;
	virtual void clean() = 0;
	
	virtual void handleEvent(Game* g) = 0;
	virtual void draw(Game* g) = 0;
	virtual void update(Game* g, double d) = 0;
};

#endif /* defined (_STATE_H_)*/