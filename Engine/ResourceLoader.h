#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include "../SDL2.0\include\SDL.h"
#include "../SDL2_image-2.0.0\include\SDL_image.h"

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>

class Sprite{
public:
	Sprite() : posOnSheet({ 0, 0, 0, 0 }){}
	Sprite(SDL_Texture * sheet, SDL_Rect position){ spritesheet = sheet; posOnSheet = position; }

	void setFlip(SDL_RendererFlip f)	{ flip = f;			  }
	void setPos(SDL_Rect p)				{ posOnSheet = p;	  }
	void setSheet(SDL_Texture* t)		{ spritesheet = t;	  }

	SDL_RendererFlip	getFlip()		{ return flip;		  }
	SDL_Rect			getPos()		{ return posOnSheet;  }
	SDL_Texture *		getTexture()	{ return spritesheet; }
private:
	SDL_RendererFlip	flip;
	SDL_Rect			posOnSheet;
	SDL_Texture *		spritesheet;
};

class ResourceLoader{
public:
	static void				addResource(const char* name, SDL_Texture* t){ resources[name] = t; }
	static void				addSprite  (const char* name, SDL_Texture * sheet, SDL_Rect position){ Sprite s = { sheet, position }; sprites[name] = s; }

	static SDL_Texture *	getResource(const char* name){ return resources[name];	}
	static Sprite			getSprite  (const char* name){ return sprites[name];	}

	static std::string		readTextFile(const char*);
	static SDL_Surface *	loadBMP		(const char*);
	static SDL_Surface *	loadImage	(const char*);

	static void clean(){ 
		for (auto r : resources){
			SDL_DestroyTexture(r.second);
		}
		IMG_Quit();
	}
private:
	ResourceLoader(){ IMG_Init(IMG_INIT_PNG); }
	static std::map<const char*, SDL_Texture*>	resources;
	static std::map<const char*, Sprite>		sprites;
};
#endif /* defined  (_RESOURCELOADER_H_) */