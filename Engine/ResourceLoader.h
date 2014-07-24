#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include "../SDL2.0\include\SDL.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class ResourceLoader{
public:
	string readTextFile(const char* p);
	SDL_Surface * loadBMP(const char* p);
private:
	SDL_Surface * surf;
};
#endif /* defined  (_RESOURCELOADER_H_) */