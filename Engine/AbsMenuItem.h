#ifndef ABSMENUITEM_H_
#define ABSMENUITEM_H_

#include "State.h"

class MenuItem{
public:
	virtual void draw(std::shared_ptr<GraphicsEngine> g) = 0;
	virtual void clean() = 0;
	virtual MenuItem &setPosition(SDL_Rect r){ position = r; return *this; }
protected:
	MenuItem() : position({ 0, 0, 0, 0 }){}
	MenuItem(SDL_Rect position) : position(position){}
	SDL_Rect position;
};

class NoTextureItem : public MenuItem{
public:
	NoTextureItem() : MenuItem(), colour({ 0, 0, 0, 0 }){}
	NoTextureItem(SDL_Rect position, SDL_Color colour = { 0, 0, 0, 0 }) :  MenuItem(position), colour(colour){}
	
	virtual void draw(std::shared_ptr<GraphicsEngine> g);
	virtual void clean(){}

	virtual NoTextureItem &setColour(SDL_Color c){ colour = c; return *this; }
protected:
	SDL_Color colour;
};

class TextureItem : public MenuItem{
public:
	TextureItem() : MenuItem(), texture(nullptr){}
	TextureItem(SDL_Rect position_, const char * text_, SDL_Color colour_, std::shared_ptr<GraphicsEngine> g);
	TextureItem(SDL_Rect position_, SDL_Texture * texture_ = nullptr) : texture(texture_){}
	
	virtual void draw(std::shared_ptr<GraphicsEngine> g);
	virtual void clean() {}

	virtual TextureItem &setTexture(const char *, SDL_Color c, std::shared_ptr<GraphicsEngine>);
	virtual TextureItem &setTexture(SDL_Texture * t)	 { texture = t; return *this; }
protected:
	SDL_Texture * texture;
};

class ExecutableMenuItem{
public:
	virtual void draw(std::shared_ptr<GraphicsEngine> g, int i) = 0;
	virtual void execute();
	virtual void clean() = 0;

	virtual int getID(){ return itemID; }

	virtual ExecutableMenuItem &setFunc(void(*f)(void));
	virtual ExecutableMenuItem &setBorderSize(int);
	virtual ExecutableMenuItem &setID(int id)				{ itemID = id; return *this; }
	virtual ExecutableMenuItem &setPosition(SDL_Rect p)		{ position = p; return *this; }
	virtual ExecutableMenuItem &setBorderCol(SDL_Color c)	{ borderColour = c; return *this; }
	virtual ExecutableMenuItem &setSelBorderCol(SDL_Color c){ selBorderColour = c; return *this; }
	virtual ExecutableMenuItem &setBackgroundColour(SDL_Color c)	{ bgColour = c;  return *this; }
protected:
	int itemID;
	void(*func)(void);
	SDL_Rect position;
	SDL_Rect border;
	SDL_Color bgColour;
	SDL_Color borderColour;
	SDL_Color selBorderColour;
	ExecutableMenuItem(int id, SDL_Rect p, SDL_Color b, SDL_Color bs) : position(p), border(position), itemID(id), borderColour(b), selBorderColour(bs){}
	ExecutableMenuItem(int id, SDL_Rect p);
	ExecutableMenuItem() : itemID(0), position({ 0, 0, 0, 0 }), border(position), borderColour({ 0, 0, 0, 0 }), selBorderColour({ 0, 0, 0, 0 }), bgColour({0,0,0,0}){}
};

class ExecNoTextureItem : public ExecutableMenuItem{
public:
	virtual void draw(std::shared_ptr<GraphicsEngine> g, int i){}
	virtual void clean() {}

	ExecNoTextureItem() : ExecutableMenuItem(){}
protected:
	ExecNoTextureItem(SDL_Rect p, int id) : ExecutableMenuItem(id, p){}
};

class ExecTextureItem : public ExecutableMenuItem{
public:
	virtual void draw(std::shared_ptr<GraphicsEngine> g, int i){}
	virtual void clean() {}

	virtual ExecTextureItem &setPosition(SDL_Rect p){
		position = p;
		textPosition = position;
		textPosition.h -= 10;
		textPosition.w -= 10;
		textPosition.x += 5;
		textPosition.y += 5;
	return *this; }
	virtual ExecTextureItem &setTexture(const char *, std::shared_ptr<GraphicsEngine> g);
	virtual ExecTextureItem &setTexture(SDL_Texture * t)	 { texture = t; return *this; }
	virtual ExecTextureItem &setFontColour(SDL_Color c)		 { fontColour = c; return *this; }
	virtual ExecTextureItem &setBackgroundColour(SDL_Color c){ background = c; return *this; }
	
	ExecTextureItem() : ExecutableMenuItem(), texture(nullptr), background({0,0,0,0}){}
protected:
	ExecTextureItem(SDL_Rect p, int id, SDL_Texture * texture_) : ExecutableMenuItem(id, p), texture(texture_), background({ 0, 0, 0, 0 }){}
	ExecTextureItem(SDL_Rect p, int id, const char * text, SDL_Color fontColour_, std::shared_ptr<GraphicsEngine> g);
	SDL_Texture * texture;
	SDL_Rect textPosition;
	SDL_Color fontColour;
	SDL_Color background;
};

class MenuButton : public ExecTextureItem{
public:
	MenuButton() : ExecTextureItem() {}
	virtual void draw(std::shared_ptr<GraphicsEngine> g, int i);
};

class ToggleButton : public ExecNoTextureItem{
public:
	ToggleButton() : ExecNoTextureItem(), altColour({ 0, 0, 0, 0 }), toggle(false){}
	ToggleButton(int id, SDL_Rect p, SDL_Color on_, SDL_Color off_) : ExecNoTextureItem(p, id), altColour(off_), toggle(false){}

	virtual void execute(){ toggle = !toggle; }
	virtual void draw(std::shared_ptr<GraphicsEngine> g, int i);

	virtual ToggleButton &setOnColour(SDL_Color c){ onColour = c; return *this; }
	virtual ToggleButton &setAltColour(SDL_Color c){ altColour = c; return *this; }

	void setToggle(bool b){ toggle = b; }
	bool getToggle(){ return toggle; }
private:
	bool toggle;
	SDL_Color onColour;
	SDL_Color altColour;
};

class  PopUpMenu : public TextureItem{
public:
	PopUpMenu() : TextureItem(), selectedButton(0){}

	virtual void draw(std::shared_ptr<GraphicsEngine> g, int i){ g->draw(texture, position); for (auto b : buttons){ b->draw(g, i); } }
	virtual PopUpMenu &addButton(ExecutableMenuItem* b){ buttons.push_back(b); return *this; }
	
	void operator++(){
		if (selectedButton != buttons.size()-1)
			selectedButton++;	}
	void operator--(){
		if (selectedButton != 0)
			selectedButton--;	}
	int getSelectedButton(){ return selectedButton; }
private:
	int selectedButton;
	std::vector<ExecutableMenuItem*> buttons;
};
#endif /* defined (_ABSMENUITEM_H_)*/