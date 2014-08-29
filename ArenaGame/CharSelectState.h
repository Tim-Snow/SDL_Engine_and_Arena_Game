#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

struct charQuad{
	SDL_GameController* c;
	SDL_Rect pos;
	MenuButton a;
};

class CharSelectState : public MenuSystem{
public:
	void init();
	void update(double d);

	CharSelectState();
private:
	TextureItem title;
	TextureItem a;
	TextureItem b;
	TextureItem c;
	TextureItem d;
	SDL_GameController * test;
};
#endif /* defined (_CHARSELECTSTATE_H_)*/