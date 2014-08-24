#include "MenuSystem.h"
#include "../ArenaGame/Game.h"

TextureItem::TextureItem(SDL_Rect position_, const char * text_, SDL_Color colour_, Game* g) : MenuItem(position_){
	texture = g->gfx->getTextTexture(text_, g->gfx->getFont(), colour_);
}

ExecutableMenuItem::ExecutableMenuItem(int id, SDL_Rect p) : borderColour({ 30, 30, 30, 50 }), selBorderColour({ 100, 100, 100, 255 }), position(p), itemID(id){
	border.h = p.h + 20;
	border.w = p.w + 20;
	border.x = p.x - 10;
	border.y = p.y - 10;
}

ExecutableMenuItem& ExecutableMenuItem::setBorderSize(int s){
	border = position;
	border.w += s;
	border.h += s;
	border.x -= (s / 2);
	border.y -= (s / 2);
	return *this;
}

ExecTextureItem::ExecTextureItem(SDL_Rect p, int id, const char * text, SDL_Color fontColour_, Game* g) : ExecutableMenuItem(id, p), fontColour(fontColour_), background({ 0, 0, 0, 0 }){
	texture = g->gfx->getTextTexture(text, g->gfx->getFont(), fontColour);
}

ExecTextureItem& ExecTextureItem::setTexture(const char * c, Game* g){
	texture = g->gfx->getTextTexture(c, g->gfx->getFont(), fontColour);
	return *this;
}

void ToggleButton::draw(Game* g, int i){
	if (i == itemID){ g->gfx->drawRect(border, selBorderColour); }
	else { g->gfx->drawRect(border, borderColour); }

	if (toggle){ g->gfx->drawRect(position, colour); }
	if(!toggle){ g->gfx->drawRect(position, altColour); }
}

void MenuButton::draw(Game* g, int i){
	if (i == itemID){ g->gfx->drawRect(border, selBorderColour); }
	else { g->gfx->drawRect(border, borderColour); }

	g->gfx->drawRect(position, background);
	g->gfx->draw(texture, position);
}

void NoTextureItem::draw(Game* g){
	g->gfx->drawRect(position, colour);
}

void TextureItem::draw(Game* g){
	g->gfx->draw(texture, position);
}

void MenuButton::execute(Game* g){
	if (nextState == NULL){	g->core.exit();	} 
	else if (nextState == &g->backState){ g->popState(); }
	else { g->pushState(nextState); }
}