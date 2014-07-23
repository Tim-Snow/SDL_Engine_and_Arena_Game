#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine/AbstractGameObj.h"

class GameObject : public AbstractGameObj{
public:
	GameObject();
	GameObject(double x, double y, int w, int h, bool grav, bool vis);
		
	void move();
	void addTextureToObject(SDL_Texture * t);

	~GameObject();
private:
protected:

};

#endif /* defined (_GAMEOBJECT_H_) */