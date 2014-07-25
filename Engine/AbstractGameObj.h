#ifndef ABSTRACTGAMEOBJ_H_
#define ABSTRACTGAMEOBJ_H_

#include "../SDL2.0\include\SDL.h"
#include "../SDL2_TTF\include\SDL_ttf.h"


struct Rect2f{
	float x, y, w, h;

	SDL_Rect getRect2(){
		SDL_Rect rect = { x, y, w, h };
		return rect;
	}
};

class AbstractGameObj{
public:
	virtual bool getVisible() = 0;
	virtual bool getGravity() = 0;
	virtual SDL_Texture * getTexture() = 0;
	virtual SDL_Rect getRect() = 0;
	virtual void addTextureToObject(SDL_Texture * t) = 0;
private:
protected:
	AbstractGameObj();
	AbstractGameObj(double x, double y, int w, int h, bool grav, bool vis);

	SDL_Texture * texture;
	Rect2f rect;
	bool visible, gravity;

	~AbstractGameObj();
};

#endif /* defined (_ABSTRACTGAMEOBJ_H_) */