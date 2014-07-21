#include "GameObject.h"

GameObject::GameObject(){
	gravity = false;
	visible = false;
	x = y = 0;
	w = h = 10;
	surf = nullptr;
}


GameObject::GameObject(double x2, double y2){
	gravity = false;
	visible = false;
	x = x2;
	y = y2;
	w = h = 10;
	surf = nullptr;
}

GameObject::GameObject(double x2, double y2, int w2){
	gravity = false;
	visible = true;
	x = x2;
	y = y2;
	w = h = w2;
	surf = nullptr;
}

GameObject::~GameObject(){
	SDL_FreeSurface(surf);
}