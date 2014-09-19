#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"
#include "Player.h"
//will also include, 'skills', 'talents', 'class responsible for save/load chars'

enum playerStates { NO_CONTROLLER, NOT_PLAYING, EDITING, CLASS_SELECT, TALENT_SELECT, SKILL_SELECT, READY };

class playerQuarter{
public:
	MENU_COMMANDS	getInput(){ return playerInput;		}
	playerStates	getState(){ return thisPlayerState; }
	void			setState(playerStates p){ thisPlayerState = p; }

	void update(double d);
	void handleEvent(std::shared_ptr<InputManager> i);
	void draw(std::shared_ptr<GraphicsEngine> g);
	void clean(){
		for (auto b : buttons){
			b->clean();
	}	}

	playerQuarter(const int i, SDL_Rect p);
private:
	const int		id;
	int				selectedButton;
	MENU_COMMANDS	playerInput;
	SDL_Rect		pos, menuPos;
	playerStates	thisPlayerState;
	TextureItem		ready, pressToJoin, noConnect, curClass;
	MenuButton		accept, cClass, talents, back, load, save, warrior, fighter, wizard, tactician;
	PopUpMenu		charClass, charSkills, charTalents;
	Player			player;
	
	SDL_Texture *	bg;
	SDL_Texture *	theChar;
	std::vector<ExecutableMenuItem*> buttons;
};

class CharSelectState : public MenuSystem{
public:
	void init();
	void update(double d);
	void handleEvent();
	void draw();

	CharSelectState() : readyPlayers(0){}
	~CharSelectState(){ 
		for (auto p : players){
			p->clean();
	}	}
private:
	int readyPlayers;
	TextureItem title;
	std::vector<playerQuarter*> players;
};

#endif /* defined (_CHARSELECTSTATE_H_)*/