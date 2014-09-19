#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine/AbstractGameObj.h"

class GameObject : public AbstractGameObj{
public:
	GameObject() : AbstractGameObj(){}
	GameObject(double x, double y, int w, int h, bool grav, bool vis);

	~GameObject(){}
private:
protected:
	void move(){}
	void update(){}
	void draw(){}

	void addTextureToObject(SDL_Texture * t){ texture = t; }

	bool getVisible()			{ return visible;			}
	bool getGravity()			{ return gravity;			}
	SDL_Rect getRect()			{ return rect.getRect2();	}
	SDL_Texture * getTexture()	{ return texture;			}
};

#endif /* defined (_GAMEOBJECT_H_) */