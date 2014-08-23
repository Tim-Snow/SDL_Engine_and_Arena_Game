#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_

#include "State.h"
#include <array>

class MenuItem{
public:
	virtual void draw(Game* g) = 0;
	virtual void clean() = 0;
protected:
	MenuItem(SDL_Rect position_ = { 0, 0, 0, 0 }) : position(position_){}
	SDL_Rect position;
};

class NoTextureItem : public MenuItem{
public:
	NoTextureItem(SDL_Rect position_, SDL_Color colour_ = { 0, 0, 0, 0 }) : colour(colour_){}
	
	virtual void draw(Game* g);
	virtual void clean(){}
protected:
	SDL_Color colour;
};

class TextureItem : public MenuItem{
public:
	TextureItem(SDL_Rect position_, const char * text_, SDL_Color colour_, Game* g);
	TextureItem(SDL_Rect position_, SDL_Texture * texture_ = nullptr) : texture(texture_){}
	
	virtual void draw(Game* g);
	virtual void clean() { SDL_DestroyTexture(texture); }
protected:
	SDL_Texture * texture;
};

class MenuButton : public TextureItem{
public:
	MenuButton(const char*, int, State*, SDL_Rect, SDL_Color, Game* g);

	void execute(Game* g);
	virtual void draw(Game* g, int);
private:
	State* nextState;
	int buttonID;
	SDL_Rect outerBorder;
};

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
	void addButton(MenuButton);
	void addItem(MenuItem*);
	MenuSystem();
protected:
	int selectedButton;

	MENU_COMMANDS menuInput;
	SDL_Texture * background;
	SDL_Color menuTextCol;
	std::vector<MenuItem*> items;
	std::vector<MenuButton> buttons;
	std::vector<MenuButton>::iterator buttonIt;
};
#endif /* defined (_MENUSYSTEM_H_)*/