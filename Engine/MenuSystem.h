#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_

#include "State.h"
#include "AbsMenuItem.h"


class MenuSystem : public State{
public:
	virtual void init(Game* g);
	virtual void clean();
	virtual void handleEvent(Game* g);
	virtual void draw(Game* g);
	virtual void update(Game* g, double d);

	void setTextColour(SDL_Color);
	SDL_Color getTextColour();
	void setBackgroundImage(SDL_Texture*);
	void addButton(ExecutableMenuItem*);
	void addItem(MenuItem*);
	MenuSystem();
protected:
	int selectedButton;

	MENU_COMMANDS menuInput;
	SDL_Texture * background;
	SDL_Color menuTextCol;
	std::vector<MenuItem*> items;
	std::vector<ExecutableMenuItem*> buttons;
};
#endif /* defined (_MENUSYSTEM_H_)*/