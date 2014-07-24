#include "GameObject.h"

GameObject::GameObject() : AbstractGameObj(){
	rect = { 0.0, 0.0, 0.0, 0.0 };
}

GameObject::GameObject(double x, double y, int w, int h, bool grav, bool vis) : AbstractGameObj(x, y, w, h, grav, vis){
	rect = { x, y, w, h };
}

void GameObject::addTextureToObject(SDL_Texture * t){	
	texture = t;
}

void GameObject::move(){
	rect.x += 0.1;
}

SDL_Rect GameObject::getRect()	{	return rect.getRect2(); }
bool GameObject::getVisible()	{	return visible; }
bool GameObject::getGravity()	{	return gravity; }
SDL_Texture * GameObject::getTexture(){	 return texture; }

GameObject::~GameObject(){}