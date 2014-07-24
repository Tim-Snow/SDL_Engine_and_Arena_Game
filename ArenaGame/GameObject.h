#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine/AbstractGameObj.h"

class GameObject : public AbstractGameObj{
public:
	GameObject();
	GameObject(double x, double y, int w, int h, bool grav, bool vis);

	void move();
	bool getVisible();
	bool getGravity();
	SDL_Rect getRect();

	SDL_Texture * getTexture();
	void addTextureToObject(SDL_Texture * t);
	
	~GameObject();
private:
protected:

};

#endif /* defined (_GAMEOBJECT_H_) */