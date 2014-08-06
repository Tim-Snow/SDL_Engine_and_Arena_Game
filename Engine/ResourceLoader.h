#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include "../SDL2.0\include\SDL.h"

#include <string>
#include <iostream>
#include <fstream>

class ResourceLoader{
public:
	std::string readTextFile(const char*);
	SDL_Surface * loadBMP(const char*);

private:
};
#endif /* defined  (_RESOURCELOADER_H_) */