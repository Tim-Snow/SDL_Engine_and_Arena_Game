#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "Settings.h"
#include "AbstractGameObj.h"
#include <string>
#include <memory>

class GraphicsEngine{
public:
	SDL_Texture * makeTextureFromSurf(SDL_Surface * s);
	SDL_Texture * getTextTexture(const char*, TTF_Font*, SDL_Color);
	TTF_Font	* getFont();
	
	int getWindowWidth();
	int getWindowHeight();
	int gcd(int a, int b);
	SDL_Rect	setRectToMiddle(int sizeW, int sizeH);

	void setTitle(std::string n);
	void setWindowSize(int w, int h);
	bool makeWindow(int w, int h, bool fullscreen);
	void setFullscreen(bool fs);

	void getPossibleResolutions();
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

	SDL_Window	*	window;
	SDL_Renderer*	renderer;
	TTF_Font	*	font;
	SDL_Texture *	texture;

	std::string name;
	bool fullscreen;
};

#endif /* defined (_GRAPHICSENGINE_H_) */