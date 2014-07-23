#ifndef ABSTRACTGAMEOBJ_H_
#define ABSTRACTGAMEOBJ_H_

#include "../SDL2.0\include\SDL.h"

class AbstractGameObj{
public:
	SDL_Texture * texture;
	SDL_Rect rect;
	double x, y;
	int w, h;
	bool visible, gravity;

	virtual void addTextureToObject(SDL_Texture * t) = 0;
private:
protected:
	AbstractGameObj();
	AbstractGameObj(double x, double y, int w, int h, bool grav, bool vis);
	~AbstractGameObj();
};

#endif /* defined (_ABSTRACTGAMEOBJ_H_) */