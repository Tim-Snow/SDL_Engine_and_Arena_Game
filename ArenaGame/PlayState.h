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
	World() : width(3000), height(3000){}
	void addObjectToWorld(GameObject o){ objects.push_back(o); }
	void handleEvent(std::shared_ptr<InputManager> input){
		for (int i = 0; i < players.size(); i++){
			players[i].handleEvent(input);
		}
	}
	void update(){
		for (int i = 0; i < players.size(); i++){
			//update viewport based on player position
			bool check = false;
			for (int j = 0; j < objects.size(); j++){
				if (players[i].collidesWith(objects[j].getPosRect()))	check = true;
				if (!check)players[i].setAir(true);
				if (check)players[i].setAir(false);
			}		
			players[i].update();
		}
		for (int i = 0; i < objects.size(); i++){
			objects[i].update();
		}
	}
	void draw(std::shared_ptr<GraphicsEngine> g){ 
		for (int i = 0; i < players.size(); i++){
			players[i].draw(g);
		}
		for (int i = 0; i < objects.size(); i++){//add function 'is contained by' to return bool depending on if rect position is inside of (or collides with) another then convert from world co ord to screen
			objects[i].draw(g); 
		} 
	}

	std::vector<Player> players;
private:
	int width, height;
	SDL_RectF viewport;	//init to screen size show everything inside rect
	//background
	std::vector<GameObject> objects;
};

class PlayState : public State{
public:
	PlayState(std::vector<Player> p){
		theLevel.players = p; 
		for (int i = 0; i < theLevel.players.size(); i++){
			theLevel.players[i].setState(PLAYER_IDLE);
			theLevel.players[i].setPosition({ i * 300, 100 });	//create 'spawner' class to find a spawn point
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