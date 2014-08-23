#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "State.h"
#include <array>

class MenuItem{
public:
	void draw(Game* g){}
protected:
	MenuItem(SDL_Rect position_ = { 0, 0, 0, 0 }) : position(position_){}
	SDL_Rect position;
};

class NoTextureItem : public MenuItem{
protected:
	NoTextureItem(SDL_Rect position_, SDL_Color colour_ = { 0, 0, 0, 0 }) : colour(colour_){}
	void draw(Game* g);
	
	SDL_Color colour;
};

class TextureItem : public MenuItem{
protected:
	TextureItem(SDL_Rect position_, const char * text_, SDL_Color colour_, Game* g);
	TextureItem(SDL_Rect position_, SDL_Texture * texture_ = nullptr) : texture(texture_){}
	void draw(Game* g);
	void clean() { SDL_DestroyTexture(texture); }
	SDL_Texture * texture;
};

class MenuText : public TextureItem{
public:
	MenuText(SDL_Rect position_, const char* text_, SDL_Color, Game* g);
};

class MenuButton : public TextureItem{
public:
	MenuButton(const char*, int, State*, SDL_Rect, SDL_Color, Game* g);

	void execute(Game* g);
	void draw(Game* g, int);
private:
	State* nextState;
	int buttonID;
	SDL_Rect outerBorder;
};

class MenuState : public State{
public:
	void init(Game* g);
	void clean();
	void handleEvent(Game* g);
	void draw(Game* g);
	void update(Game* g, double d);

	void setTextColour(SDL_Color);
	SDL_Color getTextColour();
	void setBackgroundImage(SDL_Texture*);
	void addButton(MenuButton);
	void addItem(MenuItem);
	void addTextObect(const char*, SDL_Rect);
	MenuState();
private:
	int selectedButton;

	MENU_COMMANDS menuInput;
	SDL_Texture * background;
	SDL_Color menuTextCol;
	std::vector<MenuItem> items;
	std::vector<MenuItem>::iterator itemIt;
	std::vector<MenuButton> buttons;
	std::vector<MenuButton>::iterator buttonIt;
};
#endif /* defined (_MENUSTATE_H_)*/