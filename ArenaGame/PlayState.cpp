#include "PlayState.h"

void PlayState::init(){
	t = 0.0;
	r = 350;
	cx = gfx->getWindowWidth() / 2;
	cy = gfx->getWindowHeight() / 2;
	sun = block = ResourceLoader::getResource("spritesheet");
	bg = ResourceLoader::getResource("dayBG");
	light = { 0, 0, 4, 4 };
	node a, b, c, d, e, f, g, h;
	a.setNode(500, 500);
	b.setNode(500, 564);
	c.setNode(564, 500);
	d.setNode(564, 564);
	e.setNode(628, 500);
	f.setNode(628, 564);
	g.setNode(692, 500);
	h.setNode(692, 564);
	nodes.push_back(a);
	nodes.push_back(b);
	nodes.push_back(c);
	nodes.push_back(d);
	nodes.push_back(e);
	nodes.push_back(f);
	nodes.push_back(g);
	nodes.push_back(h);
}

void PlayState::update(double d){
	t+= d * 0.0001;
	sx = (r+200)*cos(t) + cx;
	sy = r*sin(t) + cy;
	light.x = sx + 64;
	light.y = sy + 64;
}

void PlayState::handleEvent(){
	if (input->isPressed(SDLK_ESCAPE)){
		StateManager::instance().popState();
	}
}

void PlayState::draw(){
	gfx->drawFullBG(bg);

	for (int i = 0; i < nodes.size(); i++){
		gfx->drawLine(light.x, light.y, nodes.at(i).getNodeX(), nodes.at(i).getNodeY(), 1500);
	}	
	
	gfx->drawFromSpritesheet(sun, { 256, 0, 128, 128 }, { sx, sy, 128, 128 });
	gfx->drawFromSpritesheet(block, { 0, 512, 128, 128 }, { 500, 500, 64, 64 });
	gfx->drawFromSpritesheet(block, { 128, 512, 128, 128 }, { 564, 500, 64, 64 });
	gfx->drawFromSpritesheet(block, { 256, 512, 128, 128 }, { 627, 500, 64, 64 });
}

void PlayState::clean(){}