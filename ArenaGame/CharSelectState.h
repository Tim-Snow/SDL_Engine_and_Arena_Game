#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

class CharSelectState : public MenuSystem{
public:
	void init();
	void update(double d);

	CharSelectState();
private:
	TextureItem title;
};
#endif /* defined (_CHARSELECTSTATE_H_)*/