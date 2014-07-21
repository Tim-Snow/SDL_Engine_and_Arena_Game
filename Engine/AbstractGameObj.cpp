#include "AbstractGameObj.h"
#include <iostream>
AbstractGameObj::AbstractGameObj(){
	gravity = false;
	visible = true;
	x = y = 50;
	w = h = 32;
	surf = SDL_LoadBMP("test.bmp");
}


AbstractGameObj::~AbstractGameObj(){
	SDL_FreeSurface(surf);
}