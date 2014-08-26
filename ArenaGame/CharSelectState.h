#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

class CharSelectState : public MenuSystem{
public:
	void init();
	void update(double d);
	void draw();
	CharSelectState();
	SDL_Texture * t;

private:
	PlayState play;
};
#endif /* defined (_CHARSELECTSTATE_H_)*/