#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"

class TitleState : public State{
public:
	void init(Game* g);
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);
	
	TitleState();
private:
	SDL_Texture *	background;
	SDL_Texture *	title;
	SDL_Rect		titleRect;
	SDL_Texture *	welcomeMessage;
	SDL_Rect		welcomeRect;
	SDL_Color colour;
	
	MENU_COMMANDS titleInput;
};

#endif /* defined (_TITLESTATE_H_)*/