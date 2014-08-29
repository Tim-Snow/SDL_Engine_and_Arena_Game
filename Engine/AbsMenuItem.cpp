#include "MenuSystem.h"

TextureItem::TextureItem(SDL_Rect position_, const char * text_, SDL_Color colour_, std::shared_ptr<GraphicsEngine> g) : MenuItem(position_){
	texture = g->getTextTexture(text_, g->getFont(), colour_);
}

ExecutableMenuItem::ExecutableMenuItem(int id, SDL_Rect p) : borderColour({ 30, 30, 30, 50 }), selBorderColour({ 100, 100, 100, 255 }), position(p), itemID(id){
	border.h = p.h + 20;
	border.w = p.w + 20;
	border.x = p.x - 10;
	border.y = p.y - 10;
}

void ExecutableMenuItem::execute(){ 
	if (func != nullptr){
		func();
	}
}

ExecutableMenuItem& ExecutableMenuItem::setFunc(void(*f)(void)){ 
	func = f;
	return *this; 
} 

ExecutableMenuItem& ExecutableMenuItem::setBorderSize(int s){
	border = position;
	border.w += s;
	border.h += s;
	border.x -= (s / 2);
	border.y -= (s / 2);
	return *this;
}

ExecTextureItem::ExecTextureItem(SDL_Rect p, int id, const char * text, SDL_Color fontColour_, std::shared_ptr<GraphicsEngine> g) : ExecutableMenuItem(id, p), fontColour(fontColour_), background({ 0, 0, 0, 0 }){
	texture = g->getTextTexture(text, g->getFont(), fontColour);
}

ExecTextureItem& ExecTextureItem::setTexture(const char * c, std::shared_ptr<GraphicsEngine> g){
	texture = g->getTextTexture(c, g->getFont(), fontColour);
	return *this;
}

TextureItem& TextureItem::setTexture(const char * c, SDL_Color col, std::shared_ptr<GraphicsEngine> g){
	texture = g->getTextTexture(c, g->getFont(), col);
	return *this;
}

void ToggleButton::draw(std::shared_ptr<GraphicsEngine> g, int i){
	if (i == itemID){ g->drawRect(border, selBorderColour); }
	else { g->drawRect(border, borderColour); }

	if (toggle){ g->drawRect(position, onColour); }
	if(!toggle){ g->drawRect(position, altColour); }
}

void MenuButton::draw(std::shared_ptr<GraphicsEngine> g, int i){
	if (i == itemID){ g->drawRect(border, selBorderColour); }
	else { g->drawRect(border, borderColour); }

	g->drawRect(position, background);

	g->draw(texture, textPosition);
}

void NoTextureItem::draw(std::shared_ptr<GraphicsEngine> g){
	g->drawRect(position, colour);
}

void TextureItem::draw(std::shared_ptr<GraphicsEngine> g){
	g->draw(texture, position);
}