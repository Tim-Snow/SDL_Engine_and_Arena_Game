#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_

#include "State.h"
#include "AbsMenuItem.h"


class MenuSystem : public State{
public:
	virtual void init();
	virtual void clean();
	virtual void handleEvent();
	virtual void draw();
	virtual void update(double d);

	SDL_Color getTextColour(){ return menuTextCol; }
	SDL_Color getBorderColour(){ return borderCol; }
	SDL_Color getSelBorderColour(){ return selBorderCol; }
	SDL_Color getItemBgColour(){ return itemBgCol; }

	void setItemBgColour(SDL_Color c)	{ itemBgCol = c; }
	void setTextColour(SDL_Color c)		{ menuTextCol	= c; }
	void setBorderColour(SDL_Color c)	{ borderCol		= c; }
	void setSelBorderColour(SDL_Color c){ selBorderCol	= c; }
	void setBackgroundImage(SDL_Texture* t){ background = t; }
	void addButton(ExecutableMenuItem*);
	void addItem(MenuItem*);
	MenuSystem::MenuSystem() : selectedButton(0), menuInput(NONE), background(nullptr), 
		menuTextCol({ 255, 255, 255, 255 }), borderCol({ 30, 30, 30, 30 }), selBorderCol({ 100, 100, 100, 255 }), itemBgCol({0,0,0,255}){}
protected:
	int selectedButton;

	MENU_COMMANDS menuInput;
	SDL_Texture * background;
	SDL_Color menuTextCol;
	SDL_Color itemBgCol;
	SDL_Color borderCol;
	SDL_Color selBorderCol;
	std::vector<MenuItem*> items;
	std::vector<ExecutableMenuItem*> buttons;
};
#endif /* defined (_MENUSYSTEM_H_)*/