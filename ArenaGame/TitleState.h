#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "../Engine/MenuSystem.h"
#include "MenuState.h"

class TitleState : public MenuSystem{
public:
	void init(Game* g);
	void handleEvent(Game* g);
	void update(Game* g, double d);

	TitleState(){}
	MenuState mainMenu;
private:
	MENU_COMMANDS titleInput;
};

#endif /* defined (_TITLESTATE_H_)*/