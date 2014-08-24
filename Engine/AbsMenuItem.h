#ifndef ABSMENUITEM_H_
#define ABSMENUITEM_H_

#include "State.h"

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

class ExecutableMenuItem{
public:
	virtual void draw(Game* g, int i) = 0;
	virtual void execute(Game* g) = 0;
	virtual void clean() = 0;
	virtual int getID(){ return itemID; }
protected:
	int itemID;
	ExecutableMenuItem(SDL_Rect p, int id);
	SDL_Rect position;
	SDL_Rect border;
	SDL_Color borderColour;

};

class ExecNoTextureItem : public ExecutableMenuItem{
public:
	virtual void draw(Game* g, int i){}
	virtual void execute(Game* g) {}
	virtual void clean() {}
protected:
	ExecNoTextureItem(SDL_Rect p, int id, SDL_Color colour_) : ExecutableMenuItem(p, id), colour(colour_){}
	SDL_Color colour;
};

class ExecTextureItem : public ExecutableMenuItem{
public:
	virtual void draw(Game* g, int i){}
	virtual void execute(Game* g) {}
	virtual void clean() { SDL_DestroyTexture(texture); }
protected:
	ExecTextureItem(SDL_Rect p, int id, SDL_Texture * texture_) : ExecutableMenuItem(p, id), texture(texture_){}
	ExecTextureItem(SDL_Rect p, int id, const char * text, SDL_Color fontColour_, Game* g);
	SDL_Texture * texture;
	SDL_Color fontColour;
};

class MenuButton : public ExecTextureItem{
public:
	MenuButton::MenuButton(const char* text_, int buttonID_, State* state_, SDL_Rect position_, SDL_Color colour_, Game* g) : ExecTextureItem(position_, buttonID_, text_, colour_, g), nextState(state_){}
	virtual void draw(Game* g, int i);
	virtual void execute(Game* g);
	State* nextState;
};

class ToggleButton : public ExecNoTextureItem{
public:
	ToggleButton(int id, SDL_Rect p, SDL_Color on_, SDL_Color off_) : ExecNoTextureItem(p, id, on_), altColour(off_), toggle(false){}

	virtual void execute(Game* g);
	virtual void draw(Game* g, int i);
	void setToggle(bool);
	bool getToggle();
private:
	bool toggle;
	SDL_Color altColour;
};
#endif /* defined (_ABSMENUITEM_H_)*/