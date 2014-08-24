#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "../Engine/MenuSystem.h"
#include "CharSelectState.h"

class OptionsState : public MenuSystem{
public:
	void init(Game* g);
	void update(Game* g, double d);
	
	OptionsState(){}
private:
	MenuButton		* acceptButton;
	MenuButton		* backButton;
	TextureItem		* title;
	TextureItem		* fullscreen;
	TextureItem		* res;
	ToggleButton	* fullscreenTog;
	SDL_Rect posRect;
};

class LibraryState : public MenuSystem{
public:
	void init(Game* g);

	TextureItem * title;
	MenuButton * backButton;

	LibraryState(){}
};

class MenuState : public MenuSystem{
public:
	void init(Game* g);
	
	MenuState(){}
private:
	MenuButton* playButton;
	MenuButton* optionsButton;
	MenuButton* libraryButton;
	MenuButton* exitButton;

	CharSelectState charSelect;
	OptionsState optionsState;
	LibraryState libraryState;
};


#endif /* defined (_MENUSTATE_H_)*/