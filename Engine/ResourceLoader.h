#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include "../SDL2.0\include\SDL.h"
#include "../SDL2_image-2.0.0\include\SDL_image.h"

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>

class ResourceLoader{
public:
	static void				addResource(const char* name, SDL_Texture* t);
	static SDL_Texture *	getResource(const char* name);

	static std::string		readTextFile(const char*);
	static SDL_Surface *	loadBMP(const char*);
	static SDL_Surface *	loadImage(const char*);

	static void clean(){ 
		for (auto r : resources){
			SDL_DestroyTexture(r.second);
		}
		IMG_Quit();
	}
private:
	ResourceLoader(){ IMG_Init(IMG_INIT_PNG); }
	static std::map<const char*, SDL_Texture*> resources;
};
#endif /* defined  (_RESOURCELOADER_H_) */