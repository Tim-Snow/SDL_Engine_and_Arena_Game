#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

enum playerStates { NOT_PLAYING, EDITING, READY };

class playerQuarter{
public:
	MENU_COMMANDS getInput(){ return menuInput; }

	bool isReady(){ if (thisPlayerState == READY){ return true; } else return false; }

	void update(double d);
	void handleEvent(std::shared_ptr<InputManager> i);
	void draw(std::shared_ptr<GraphicsEngine> g);

	playerQuarter(int i, SDL_Rect p);
private:
	int		id,		selectedButton;
	MENU_COMMANDS	menuInput;
	playerStates	thisPlayerState;
	SDL_Rect		pos;
	SDL_Texture *	bg;
	SDL_Texture *	theChar;

	TextureItem		ready;
	TextureItem		pressToJoin;
	MenuButton		accept;
	MenuButton		charClass;
	MenuButton		talents;
	MenuButton		back;
	MenuButton		load;
	MenuButton		save;

	std::vector<ExecutableMenuItem*>	buttons;
};

class CharSelectState : public MenuSystem{
public:
	void init();
	void update(double d);
	void handleEvent();
	void draw();

	CharSelectState(){}
private:
	int readyPlayers;
	TextureItem title;
	SDL_Rect playMessageRect;
	std::vector<playerQuarter*> players;
};

#endif /* defined (_CHARSELECTSTATE_H_)*/