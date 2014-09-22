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

class PlayState : public State{
public:
	PlayState(std::vector<Player> p){ players = p; }
	void init();
	void clean();

	void update(double d);
	void handleEvent();
	void draw();
private:
	SDL_Texture * sun;
	SDL_Texture * block;
	SDL_Texture * bg;

	SDL_Rect light;

	int sx, sy , cx, cy, r;
	double t;

	std::vector<Player> players;
	std::vector<node>	nodes;
};
#endif /* defined (_PLAYSTATE_H_)*/