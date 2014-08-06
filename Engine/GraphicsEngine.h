#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "AbstractGameObj.h"
#include <string>

class GraphicsEngine{
public:
	GraphicsEngine();
	~GraphicsEngine();

	SDL_Texture * makeTextureFromSurf(SDL_Surface * s); 

	int getWindowWidth();
	int getWindowHeight();

	bool makeWindow(int w, int h);
	void setWindowSize(int w, int h);
	void toggleFullscreen();
	void drawFullBG(SDL_Texture*);
	void draw(SDL_Texture*, SDL_Rect);

	void clearDisplay();
	void updateDisplay();
	void setTitle(std::string n);
	void drawSquare(int x, int y, int w, int r, int g, int b);
	void drawRect(int x, int y, int w, int h, int r, int g, int b);
private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;

	std::string name;
	bool fullscreen;
};

#endif /* defined (_GRAPHICSENGINE_H_) */