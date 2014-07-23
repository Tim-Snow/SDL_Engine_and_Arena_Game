#include "GameObject.h"

GameObject::GameObject() : AbstractGameObj(){}

GameObject::GameObject(double x, double y, int w, int h, bool grav, bool vis) : AbstractGameObj(x, y, w, h, grav, vis){
	rect.h = h;
	rect.w = w;
	rect.x = x;
	rect.y = y;
}

void GameObject::addTextureToObject(SDL_Texture * t){
	texture = t;
}

void GameObject::move(){
	x += 0.1;
}

GameObject::~GameObject(){
}