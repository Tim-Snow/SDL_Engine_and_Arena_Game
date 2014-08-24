#include "CharSelectState.h"
#include "Game.h"


CharSelectState::CharSelectState(){}

void CharSelectState::init(Game* g){
	setBackgroundImage(g->getTexture("res/titleBackground.png"));
	setTextColour({ 30, 200, 60, 255 });
	setBorderColour({ 0, 100, 0, 55 });
	setSelBorderColour({ 60, 255, 100, 255 });
	setItemBgColour({ 30, 30, 155, 255 });
	SDL_Surface * s = g->res->loadImage("res/level.png");
	t = g->gfx->makeTextureFromSpritesheet(s, {0,0,128,128});
	TextureItem * title = new TextureItem({ g->gfx->getWindowWidth() / 2 - 100, 10, 200, 75 }, "Char Select", getTextColour(), g);
	MenuButton * ready1 = new MenuButton("Ready", 0, &play, { 10, g->gfx->getWindowHeight() - 200, 50, 50 }, {255,255,255,255}, g);
	//addButton(ready1);
	//addItem(title);
}
void CharSelectState::draw(Game* g){
	g->gfx->drawFullBG(background);
	g->gfx->drawFromSpritesheet(t, { 0, 0, 128, 128 }, { 10, 100, g->gfx->getWindowWidth() / 4 - 20, g->gfx->getWindowHeight() - 150 });
	g->gfx->drawFromSpritesheet(t, { 0, 0, 128, 128 }, { (g->gfx->getWindowWidth() / 4), 100, g->gfx->getWindowWidth() / 4 - 20, g->gfx->getWindowHeight() - 150 });
	g->gfx->drawFromSpritesheet(t, { 0, 0, 128, 128 }, { (g->gfx->getWindowWidth() / 4) * 2, 100, g->gfx->getWindowWidth() / 4 - 20, g->gfx->getWindowHeight() - 150 });
	g->gfx->drawFromSpritesheet(t, { 0, 0, 128, 128 }, { (g->gfx->getWindowWidth() / 4) * 3, 100, g->gfx->getWindowWidth() / 4 - 20, g->gfx->getWindowHeight() - 150 });
	for (auto item : items){
		item->draw(g);
	}

	for (auto button : buttons){
		button->draw(g, selectedButton);
	}
}
void CharSelectState::update(Game* g, double d){
	if (menuInput == BACK)
		g->popState();
}
