#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine\GraphicsEngine.h"
#include "../Engine\2DPhysicsEngine.h"

class GameObject{
public:
	GameObject() 
		: worldPos({ 0.00, 0.00 }), screenPos({ 0.00, 0.00 }), width(0.00), height(0.00), visible(false), gravity(false), scale(1.00), flipped(false), velocity({ 0.00, 0.00 }), fwidth(0.00), fheight(0.00){}
	GameObject(float width, float height, bool vis = false, bool grav = false, bool flip = false)
		: worldPos({ 0.00, 0.00 }), screenPos({ 0.00, 0.00 }), width(width), height(height), visible(vis), gravity(grav), scale(1.00), flipped(flip), velocity({ 0.00, 0.00 }), fwidth(width), fheight(height){}

	virtual void update(){ setPosition({ worldPos.x + velocity.x, worldPos.y + velocity.y }); }
	virtual void draw(std::shared_ptr<GraphicsEngine> g){ g->drawFromSpritesheet(sprite, { screenPos.x, screenPos.y, fwidth, fheight}); }

	virtual void			addSpriteToObject(Sprite s)	{ sprite		= s;		}
	virtual void			setVelocity(SDL_PointF v)	{ velocity		= v;		}
	virtual void			setYVel(float y)			{ velocity.y	= y;		}
	virtual void			setXVel(float x)			{ velocity.x	= x;		}
	virtual void			setPosition(SDL_PointF p)	{ worldPos  = { p.x, p.y }; }
	virtual void			setScreenPos(SDL_PointF p)	{ screenPos = { p.x, p.y }; }
	virtual void			setScale(float f){
		if (scale != f){
			scale = f;
			fwidth	= (float)width	* scale;	
			fheight	= (float)height	* scale;
		}
	}

	virtual SDL_PointF&		getVelocity()	{ return	velocity;									}
	virtual SDL_PointF&		getPosition()	{ return	worldPos;									}
	virtual SDL_PointF&		getScreenPos()	{ return	screenPos;									}
	virtual SDL_RectF		getPosRect()	{ return  { screenPos.x, screenPos.y, fwidth, fheight };}
	virtual float			getScale()		{ return	scale;										}
	virtual bool			getVisible()	{ return	visible;									}
	virtual bool			getGravity()	{ return	gravity;									}

	virtual void			isFlipped(bool b){
		if (flipped != b)	flipped = b;
		if (flipped)		sprite.setFlip(SDL_FLIP_HORIZONTAL);
		else { 				sprite.setFlip(SDL_FLIP_NONE); 	}	}

protected:
	//add screen + world pos to allow camera
	int			width,		height; //original size
	float		scale,		fwidth,		fheight;	//for zooming camera
	bool		flipped,	gravity,	visible;
	SDL_PointF	screenPos;	SDL_PointF	worldPos;	SDL_PointF  velocity;
	Sprite		sprite;
};

#endif /* defined (_GAMEOBJECT_H_) */