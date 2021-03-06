#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "../SDL2.0\include\SDL.h"
#include "../SDL2_TTF\include\SDL_ttf.h"
#include "Settings.h"
#include <memory>

class GraphicsEngine{
public:
	SDL_Texture * makeTextureFromSurf(SDL_Surface * s);
	SDL_Texture * makeTextureFromSpritesheet(SDL_Surface * s, SDL_Rect);
	SDL_Texture * getTextTexture(const char*, TTF_Font*, SDL_Color);
	TTF_Font	* getFont();
	
	int			getWindowWidth();
	int			getWindowHeight();
	int			gcd(int a, int b);
	SDL_Rect	setRectToMiddle(int sizeW, int sizeH);
	
	bool makeWindow(int w, int h, bool fullscreen);
	void getPossibleResolutions();
	void setTitle(std::string n);
	void setWindowSize(int w, int h);
	void setFullscreen(bool fs);
	void updateDisplay();
	void clearDisplay();

	void drawFullBG(SDL_Texture*);
	void draw(SDL_Texture*, SDL_Rect);
	void drawFromSpritesheet(Sprite, SDL_Rect);
	void drawSquare(int x, int y, int w, int r, int g, int b);
	void drawRect(int x, int y, int w, int h, int r, int g, int b);
	void drawRect(SDL_Rect rect, int r, int g, int b);
	void drawRect(SDL_Rect rect, SDL_Color c);
	void drawLine(int x1, int y1, int x2, int y2, int length);

	GraphicsEngine();
	~GraphicsEngine();
private:
	int ratio, widthMult, heightMult;
	int windowedWidth, windowedHeight;

	Uint32			flags;
	SDL_DisplayMode currentDisplay;
	SDL_Window	*	window;
	SDL_Renderer*	renderer;
	TTF_Font	*	font;
	SDL_Texture *	texture;
	SDL_Surface *	surf;
	const char	*	name;
	bool			fullscreen;
};

#endif /* defined (_GRAPHICSENGINE_H_) */