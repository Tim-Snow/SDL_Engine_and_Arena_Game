#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "MenuState.h"
#include "../Engine/MenuSystem.h"

class TitleState : public MenuSystem{
public:
	void init();
	void handleEvent();
	void update(double d);

	TitleState(){}
private:
	MENU_COMMANDS titleInput;
};

#endif /* defined (_TITLESTATE_H_)*/