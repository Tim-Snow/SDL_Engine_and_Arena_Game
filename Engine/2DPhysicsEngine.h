#ifndef PHYSICS_ENGINE_H_
#define PHYSICS_ENGINE_H_

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

typedef struct 
{
	bool leftCollision, rightCollision, topCollision, bottomCollision;
} boxCollision;

class PhysicsEngine{
public:
	static void vectorTranslate(SDL_PointF &pos, SDL_PointF vel, float scale){
		pos.x += vel.x;
		pos.y += vel.y;
	}

	static void vectorScale(){}
	static void vectorRotate(){}

	static void vectorWorldToScreen(SDL_PointF &screenPos, SDL_PointF worldPos, float scale, SDL_RectF camera){
		screenPos.x = (worldPos.x * scale) - camera.x;
		screenPos.y = (worldPos.y * scale) - camera.y;
	}

	static bool collidesWith(SDL_RectF obj1, SDL_RectF obj2)	{
		return !(obj1.x >= obj2.x + obj2.w	|| obj1.x + obj1.w <= obj2.x
			  || obj1.y >= obj2.y + obj2.h	|| obj1.y + obj1.h <= obj2.y);
	}

	static boxCollision collidesWhere(SDL_RectF obj1, SDL_RectF obj2){
		boxCollision result;
		result.bottomCollision = result.leftCollision = result.rightCollision = result.topCollision
			= false;
		obj1.w -= obj1.w / 10; obj1.h -= obj1.h / 10;
		obj1.x += obj1.w / 20;
		SDL_RectF topBox, botBox, leftBox, rightBox;
		topBox =	leftBox =	rightBox =	obj1;
		leftBox.x -= obj1.w / 10;	rightBox.x += obj1.w / 10;
		botBox = { obj1.x, (obj1.y + obj1.h), obj1.w, obj1.h/10 };

		if (collidesWith(topBox,   obj2))	result.topCollision	   = true;
		if (collidesWith(leftBox,  obj2))	result.leftCollision   = true;
		if (collidesWith(rightBox, obj2))	result.rightCollision  = true;
		if (collidesWith(botBox,   obj2))	result.bottomCollision = true;
		return result;
	}
};

#endif /* defined (_PHYSICS_ENGINE_H_) */