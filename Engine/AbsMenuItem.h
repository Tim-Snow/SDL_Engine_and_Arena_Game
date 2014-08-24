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

	virtual ExecutableMenuItem &setBorderSize(int);
	virtual ExecutableMenuItem &setID(int id)				{ itemID = id; return *this; }
	virtual ExecutableMenuItem &setPosition(SDL_Rect p)		{ position = p; return *this; }
	virtual ExecutableMenuItem &setBorderCol(SDL_Color c)	{ borderColour = c; return *this; }
	virtual ExecutableMenuItem &setSelBorderCol(SDL_Color c){ selBorderColour = c; return *this; }
	virtual ExecutableMenuItem &setBackgroundColour(SDL_Color c)	{ return *this; } //
	virtual ExecutableMenuItem &setTexture(SDL_Texture * t)			{ return *this; } //
	virtual ExecutableMenuItem &setTexture(const char *, Game* g)	{ return *this; } //
	virtual ExecutableMenuItem &setFontColour(SDL_Color)			{ return *this; } //
	virtual ExecutableMenuItem &setState(State* s)					{ return *this; } //
protected:
	int itemID;
	SDL_Rect position;
	SDL_Rect border;
	SDL_Color borderColour;
	SDL_Color selBorderColour;
	ExecutableMenuItem(int id, SDL_Rect p, SDL_Color b, SDL_Color bs) : position(p), border(position), itemID(id), borderColour(b), selBorderColour(bs){}
	ExecutableMenuItem(int id, SDL_Rect p);
	ExecutableMenuItem() : itemID(0), position({ 0, 0, 0, 0 }), border(position), borderColour({ 0, 0, 0, 0 }), selBorderColour({ 0, 0, 0, 0 }){}
};

class ExecNoTextureItem : public ExecutableMenuItem{
public:
	virtual void draw(Game* g, int i){}
	virtual void execute(Game* g) {}
	virtual void clean() {}

	virtual ExecutableMenuItem &setBackgroundColour(SDL_Color c){ colour = c; return *this; }
protected:
	ExecNoTextureItem() : ExecutableMenuItem(), colour({ 0, 0, 0, 0 }){}
	ExecNoTextureItem(SDL_Rect p, int id, SDL_Color colour_) : ExecutableMenuItem(id, p), colour(colour_){}
	SDL_Color colour;
};

class ExecTextureItem : public ExecutableMenuItem{
public:
	virtual void draw(Game* g, int i){}
	virtual void execute(Game* g) {}
	virtual void clean() { SDL_DestroyTexture(texture); }

	virtual ExecTextureItem &setTexture(const char *, Game* g);
	virtual ExecTextureItem &setTexture(SDL_Texture * t)	 { texture = t; return *this; }
	virtual ExecTextureItem &setFontColour(SDL_Color c)		 { fontColour = c; return *this; }
	virtual ExecTextureItem &setBackgroundColour(SDL_Color c){ background = c; return *this; }
protected:
	ExecTextureItem() : ExecutableMenuItem(), texture(nullptr), background({0,0,0,0}){}
	ExecTextureItem(SDL_Rect p, int id, SDL_Texture * texture_) : ExecutableMenuItem(id, p), texture(texture_), background({ 0, 0, 0, 0 }){}
	ExecTextureItem(SDL_Rect p, int id, const char * text, SDL_Color fontColour_, Game* g);
	SDL_Texture * texture;
	SDL_Color fontColour;
	SDL_Color background;
};

class MenuButton : public ExecTextureItem{
public:
	MenuButton() : ExecTextureItem(), nextState(nullptr) {}
	MenuButton(const char* text_, int buttonID_, State* state_, SDL_Rect position_, SDL_Color colour_, Game* g) : ExecTextureItem(position_, buttonID_, text_, colour_, g), nextState(state_){}
	virtual void draw(Game* g, int i);
	virtual void execute(Game* g);

	virtual MenuButton &setState(State* s){ nextState = s; return *this; }
private:
	State* nextState;
};

class ToggleButton : public ExecNoTextureItem{
public:
	ToggleButton() : ExecNoTextureItem(), altColour({ 0, 0, 0, 0 }), toggle(false){}
	ToggleButton(int id, SDL_Rect p, SDL_Color on_, SDL_Color off_) : ExecNoTextureItem(p, id, on_), altColour(off_), toggle(false){}

	virtual void execute(Game* g){ toggle = !toggle; }
	virtual void draw(Game* g, int i);

	void setToggle(bool b){ toggle = b; }
	bool getToggle(){ return toggle; }
private:
	bool toggle;
	SDL_Color altColour;
};
#endif /* defined (_ABSMENUITEM_H_)*/