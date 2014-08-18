#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "State.h"
#include <array>

class MenuState : public State{
public:
	static MenuState& instance()
	{
		static MenuState *instance = new MenuState();
		return *instance;
	}

	void init();
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);
protected:

private:
	MenuState();

	SDL_Texture * mBackground;
	SDL_Texture * buttons[5];
};






#endif /* defined (_MENUSTATE_H_)*/