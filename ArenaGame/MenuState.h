#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "../Engine/MenuSystem.h"
#include "CharSelectState.h"

class OptionsState : public MenuSystem{
public:
	void init();
	void update(double);

	OptionsState(){}
private:
	MenuButton		acceptButton;
	MenuButton		backButton;
	TextureItem		title;
	TextureItem		fullscreen;
	TextureItem		res;
	ToggleButton	fullscreenTog;
	SDL_Rect		posRect;
};

class LibraryState : public MenuSystem{
public:
	void init();

	LibraryState(){}
private:
	TextureItem title;
	MenuButton	backButton;
};

class MenuState : public MenuSystem{
public:
	void init();
	
	MenuState(){}
private:
	MenuButton playButton;
	MenuButton optionsButton;
	MenuButton libraryButton;
	MenuButton exitButton;
};


#endif /* defined (_MENUSTATE_H_)*/