#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

class OptionsState : public MenuSystem{
public:
	void init(Game* g);
	void update(Game* g, double d);

	MenuButton * acceptButton;
	MenuButton * backButton;
	TextureItem * title;
	OptionsState(){}
private:
	SDL_Rect posRect;
	ToggleButton * fullscreenTog;
};

class LibraryState : public MenuSystem{
public:
	void init(Game* g);

	LibraryState(){}
};

class MenuState : public MenuSystem{
public:
	void init(Game* g);
	
	MenuState(){}
	PlayState playState;
	OptionsState optionsState;
	LibraryState libraryState;
};


#endif /* defined (_MENUSTATE_H_)*/