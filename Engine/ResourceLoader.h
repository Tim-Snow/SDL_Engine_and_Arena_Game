#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include "../SDL2.0\include\SDL.h"
#include "../SDL2_image-2.0.0\include\SDL_image.h"

#include <string>
#include <iostream>
#include <fstream>

class ResourceLoader{
public:
	static ResourceLoader& instance(){
		static ResourceLoader *instance = new ResourceLoader();
		return *instance;
	}

	std::string readTextFile(const char*);
	SDL_Surface * loadBMP(const char*);
	SDL_Surface * loadImage(const char*);
	~ResourceLoader(){ IMG_Quit(); }
private:
	ResourceLoader(){ IMG_Init(IMG_INIT_PNG); }
};
#endif /* defined  (_RESOURCELOADER_H_) */