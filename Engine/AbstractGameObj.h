#ifndef ABSTRACTGAMEOBJ_H_
#define ABSTRACTGAMEOBJ_H_

#include "../SDL2.0\include\SDL.h"

class AbstractGameObj{
public:
	AbstractGameObj();
	~AbstractGameObj();

	SDL_Surface * surf;
	double x, y;
	int w, h;
	bool visible, gravity;
private:

protected:

};

#endif /* defined (_ABSTRACTGAMEOBJ_H_) */