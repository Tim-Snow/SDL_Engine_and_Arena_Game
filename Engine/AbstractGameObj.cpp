#include "AbstractGameObj.h"
#include <iostream>
AbstractGameObj::AbstractGameObj(){
	gravity = false;
	visible = false;
	x = y = 0;
	w = h = 0;
	surf = nullptr;
}


AbstractGameObj::~AbstractGameObj(){
	SDL_FreeSurface(surf);
}