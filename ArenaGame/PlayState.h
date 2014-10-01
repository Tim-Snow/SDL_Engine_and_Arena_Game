#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "../Engine/MenuSystem.h"
#include "Player.h"

struct node{
	int x, y;
	
	void setNode(int x2, int y2){ x = x2; y = y2; }
	int getNodeX(){ return x; }
	int getNodeY(){ return y; }
};

class World{
public:
	World() : width(3000), height(3000), viewport({ 0, 0, 0, 0 }), viewportZoom(1.00){}

	void initViewport(std::shared_ptr<GraphicsEngine> g){
		viewport.w = g->getWindowWidth();
		viewport.h = g->getWindowHeight();
	}

	void zoomOut()	{ if (viewportZoom > 0.20) viewportZoom -= 0.001; }
	void zoomIn()	{ if (viewportZoom < 1.50) viewportZoom += 0.001; }

	void viewportFollow(std::vector<Player> &players){
		SDL_RectF outerRect = { viewport.x + (viewport.w / 5), viewport.y + (viewport.h / 10), viewport.w - ((viewport.w / 5) * 2), viewport.h - ((viewport.h / 10) * 2) };
		SDL_RectF innerRect = { viewport.x + (viewport.w / 3), viewport.y + (viewport.h / 5), viewport.w - ((viewport.w / 3) * 2), viewport.h - ((viewport.h / 5) * 2) };
		bool zoomO = false;
		for (int i = 0; i < players.size(); i++){
			if (!zoomO){
				if (players[i].getPosRect().x < outerRect.x){
					viewport.x--;	zoomO = true;
				}
				else if (players[i].getPosRect().x + players[i].getPosRect().w > outerRect.x + outerRect.w){
					viewport.x++;	zoomO = true;
				}
				else if (players[i].getPosRect().y < outerRect.y){
					viewport.y--;	zoomO = true;
				}
				else if (players[i].getPosRect().y + players[i].getPosRect().h > outerRect.y + outerRect.h){
					viewport.y++;	zoomO = true;
				} else if (PhysicsEngine::collidesWith(players[i].getPosRect(), innerRect) && !zoomO){ zoomIn(); }
			} else { //another player is also on outside edge
				if (players[i].getPosRect().x < outerRect.x || players[i].getPosRect().x + players[i].getPosRect().w > outerRect.x + outerRect.w
					|| players[i].getPosRect().y < outerRect.y || players[i].getPosRect().y + players[i].getPosRect().h > outerRect.y + outerRect.h){
					zoomOut();
				}
			}
		}
	}
	
	void addObjectToWorld(GameObject o)	{ objects.push_back(o); }

	void handleEvent(std::shared_ptr<InputManager> input){
		for (int i = 0; i < players.size(); i++){
			players[i].handleEvent(input);
		}
	}
	void update(){ 
		for (int i = 0; i < players.size(); i++){
			players[i].setScale(viewportZoom);
			bool check = false;
			bool bounce = false;
			for (int j = 0; j < objects.size(); j++){
				if (PhysicsEngine::collidesWhere(players[i].getPosRect(), objects[j].getPosRect()).bottomCollision)
					check = true;	//air check
				if (PhysicsEngine::collidesWhere(players[i].getPosRect(), objects[j].getPosRect()).rightCollision ||
					PhysicsEngine::collidesWhere(players[i].getPosRect(), objects[j].getPosRect()).leftCollision &&
					!check)			//wall check
					bounce = true;
				
				if (PhysicsEngine::collidesWhere(players[i].getPosRect(), objects[j].getPosRect()).topCollision)
					players[i].setVelocity({ players[i].getVelocity().x, 0 }); //ceiling check
			}		
			if (!check)players[i].setAir(true);
			if (check)players[i].setAir(false);
			players[i].update();
			if (bounce)	players[i].setVelocity({ -players[i].getVelocity().x, players[i].getVelocity().y });
			PhysicsEngine::vectorTranslate(players[i].getPosition(), players[i].getVelocity(), players[i].getScale());
			PhysicsEngine::vectorWorldToScreen(players[i].getScreenPos(), players[i].getPosition(), viewportZoom, viewport);
		}
		for (int i = 0; i < objects.size(); i++){
			objects[i].setScale(viewportZoom);
			objects[i].update();
			PhysicsEngine::vectorWorldToScreen(objects[i].getScreenPos(), objects[i].getPosition(), viewportZoom, viewport);
		}
		viewportFollow(players);
	}
	void draw(std::shared_ptr<GraphicsEngine> g){ 
		for (int i = 0; i < objects.size(); i++){
			objects[i].draw(g); 
		} 
		for (int i = 0; i < players.size(); i++){
			players[i].draw(g);
		}
	}

	std::vector<Player> players;
private:
	int			width, height;
	SDL_RectF	viewport;	//init to screen size show everything inside rect
	float		viewportZoom;

	std::vector<GameObject> objects;
};

class PlayState : public State{
public:
	PlayState(std::vector<Player> p){
		theLevel.players = p; 
		for (int i = 0; i < theLevel.players.size(); i++){
			theLevel.players[i].setState(PLAYER_IDLE);
			theLevel.players[i].setPosition({ i * 300.00, 100.00 });	//create 'spawner' class to find a spawn point
		}
	}
	void init();
	void clean();

	void update(double d);
	void handleEvent();
	void draw();
private:
	//move world objects
	//add hud
	World theLevel;
	Sprite sun;
	Sprite block;

	SDL_Texture * bg;
	SDL_Rect light;

	int sx, sy , cx, cy, r;
	double t;

	std::vector<node>	nodes;
};
#endif /* defined (_PLAYSTATE_H_)*/