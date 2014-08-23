#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "Settings.h"
#include "AbstractGameObj.h"
#include <string>

class GraphicsEngine{
public:
	SDL_Texture * makeTextureFromSurf(SDL_Surface * s); 

	int getWindowWidth();
	int getWindowHeight();

	void setTitle(std::string n);
	void setWindowSize(int w, int h);
	bool makeWindow(int w, int h, bool fullscreen);
	void toggleFullscreen();

	void updateDisplay();
	void clearDisplay();
	void drawFullBG(SDL_Texture*);
	void draw(SDL_Texture*, SDL_Rect);
	void drawFromSpritesheet(SDL_Texture*, SDL_Rect, SDL_Rect);
	void drawSquare(int x, int y, int w, int r, int g, int b);
	void drawRect(int x, int y, int w, int h, int r, int g, int b);
	void drawRect(SDL_Rect rect, int r, int g, int b);
	void drawRect(SDL_Rect rect, SDL_Color c);

	GraphicsEngine();
	~GraphicsEngine();
private:
	int windowedWidth, windowedHeight, fullWidth, fullHeight;
	Uint32 flags;
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;

	std::string name;
	bool fullscreen;
};

#endif /* defined (_GRAPHICSENGINE_H_) */