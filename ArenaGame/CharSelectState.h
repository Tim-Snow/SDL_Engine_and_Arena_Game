#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

class CharSelectState : public MenuSystem{
public:
	void init(Game* g);
	void update(Game* g, double d);
	void draw(Game* g);
	CharSelectState();
	SDL_Texture * t;

private:
	PlayState play;
};
#endif /* defined (_CHARSELECTSTATE_H_)*/