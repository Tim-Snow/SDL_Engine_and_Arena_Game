#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine\GraphicsEngine.h"

typedef struct
{
	float x, y;
	float w, h;
} SDL_RectF;

typedef struct
{
	float x;
	float y;
} SDL_PointF;

class GameObject{
public:
	GameObject() 
		: pos({ 0.0, 0.0 }), width(0),     height(0),      visible(false),   gravity(false), scale(1.00), flipped(false), xVel(0.00), yVel(0.00){}
	GameObject(int width, int height, bool vis = false, bool grav = false, bool flip = false)
		: pos({ 0.0, 0.0 }), width(width), height(height), visible(vis),	 gravity(grav),  scale(1.00), flipped(flip),  xVel(0.00), yVel(0.00){}

	virtual void update(){ setPosition({ pos.x + xVel, pos.y + yVel }); }
	virtual void draw(std::shared_ptr<GraphicsEngine> g){ g->drawFromSpritesheet(sprite, { pos.x, pos.y, width, height}); }

	virtual bool			collidesWith(SDL_RectF obj)	{
		SDL_RectF thisObj = { pos.x, pos.y, width, height };

		return !(obj.x > thisObj.x + thisObj.w
			|| obj.x + obj.w < thisObj.x
			|| obj.y > thisObj.y + thisObj.h
			|| obj.y + obj.h < thisObj.y);
	}
	virtual void			addSpriteToObject(Sprite s)	{ sprite = s;			}
	virtual void			setYVel(float y)			{ yVel = y;				}
	virtual void			setXVel(float x)			{ xVel = x;				}
	virtual void			setPosition(SDL_PointF p)	{ pos = { p.x, p.y };	}
	virtual void			setScale(float f)			{ scale = f;			}

	virtual SDL_RectF		getPosRect()	{ return { pos.x, pos.y, width, height };	}
	virtual SDL_PointF		getPosition()	{ return { pos.x, pos.y };					}
	virtual float			getScale()		{ return scale;								}
	virtual bool			getVisible()	{ return visible;							}
	virtual bool			getGravity()	{ return gravity;							}

	virtual void			isFlipped(bool b){
		if (flipped != b)	flipped = b;
		if (flipped)		sprite.setFlip(SDL_FLIP_HORIZONTAL);
		else { 				sprite.setFlip(SDL_FLIP_NONE); 	}	}

protected:
	int			width,	 height;
	float		scale,	 xVel,	  yVel;
	bool		flipped, gravity, visible;
	SDL_PointF	pos;	 Sprite	  sprite;
};

#endif /* defined (_GAMEOBJECT_H_) */