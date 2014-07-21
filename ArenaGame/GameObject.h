#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine/AbstractGameObj.h"

class GameObject : public AbstractGameObj{
public:
	GameObject();
	GameObject(double x, double y);
	GameObject(double x, double y, int w);
	~GameObject();
private:
protected:
};

#endif /* defined (_GAMEOBJECT_H_) */