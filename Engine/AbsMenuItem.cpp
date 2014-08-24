#include "MenuSystem.h"
#include "../ArenaGame/Game.h"

ExecutableMenuItem::ExecutableMenuItem(SDL_Rect p, int id) : borderColour({ 30, 30, 30, 255 }), position(p), itemID(id){
	border.h = p.h + 20;
	border.w = p.w + 20;
	border.x = p.x - 10;
	border.y = p.y - 10;
}

ExecTextureItem::ExecTextureItem(SDL_Rect p, int id, const char * text, SDL_Color fontColour_, Game* g) : ExecutableMenuItem(p, id), fontColour(fontColour_){
	texture = g->gfx->getTextTexture(text, g->gfx->getFont(), fontColour);
}

TextureItem::TextureItem(SDL_Rect position_, const char * text_, SDL_Color colour_, Game* g) : MenuItem(position_){
	texture = g->gfx->getTextTexture(text_, g->gfx->getFont(), colour_);
}

void ToggleButton::execute(Game* g){
	toggle = !toggle;
}

void ToggleButton::setToggle(bool b){ toggle = b; }

bool ToggleButton::getToggle(){ return toggle; }

void ToggleButton::draw(Game* g, int i){
	if (i == itemID){ g->gfx->drawRect(border, 200, 200, 200); }
	else { g->gfx->drawRect(border, borderColour); }

	if (toggle){ g->gfx->drawRect(position, colour); }
	if(!toggle){ g->gfx->drawRect(position, altColour); }
}

void MenuButton::draw(Game* g, int i){
	if (i == itemID){ g->gfx->drawRect(border, 200, 200, 200); }
	else { g->gfx->drawRect(border, borderColour); }

	g->gfx->drawRect(position, 0, 0, 0);
	g->gfx->draw(texture, position);
}

void MenuButton::execute(Game* g){
	if (nextState == NULL){	g->core.exit();	} 
	else if (nextState == &g->backState || nextState == &g->acceptState){ g->popState(); }
	else { g->pushState(nextState); }
}

void NoTextureItem::draw(Game* g){
	g->gfx->drawRect(position, colour);
}

void TextureItem::draw(Game* g){
	g->gfx->draw(texture, position);
}