#include "PlayState.h"

void PlayState::init(){
	t = 0.0;
	r = 350;
	cx = gfx->getWindowWidth() / 2;
	cy = gfx->getWindowHeight() / 2;
	
	GameObject g = { 256, 256, true, false, true };
	block = ResourceLoader::getSprite("Ground");
	g.addSpriteToObject(block);
	g.setPosition({ 0.0, 500.0 });
	theLevel.addObjectToWorld(g);
	//theLevel.addObjectToWorld(g);
	//g.setPosition({ 256.0, 500.0 });
	g.setPosition({ 600.0, 500.0 });
	theLevel.addObjectToWorld(g);

	sun = ResourceLoader::getSprite("Sun");
	bg = ResourceLoader::getResource("dayBG");
	light = { 0, 0, 4, 4 };
}

void PlayState::update(double d){
	theLevel.update();

	t+= d * 0.0001;
	sx = (r+200)*cos(t) + cx;
	sy = r*sin(t) + cy;
	light.x = sx + 64;
	light.y = sy + 64;
}

void PlayState::handleEvent(){
	theLevel.handleEvent(input);

	if (input->isPressed(SDLK_ESCAPE))
		StateManager::instance().popState();
}

void PlayState::draw(){
	gfx->drawFullBG(bg);
	gfx->drawFromSpritesheet(sun, { sx, sy, 128, 128 });
	//for (int i = 0; i < nodes.size(); i++){
	//	gfx->drawLine(light.x, light.y, nodes.at(i).getNodeX(), nodes.at(i).getNodeY(), 1500);
	//}	
	theLevel.draw(gfx);
}

void PlayState::clean(){}