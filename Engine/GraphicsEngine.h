#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "AbstractGameObj.h"
#include <string>


class GraphicsEngine{
public:
	GraphicsEngine();
	~GraphicsEngine();

	void draw(AbstractGameObj *g);
	void clearDisplay();
	void updateDisplay();
	bool makeWindow(int w, int h);
	void setTitle(std::string n);
	void drawSquare(int x, int y, int w, int r, int g, int b);
private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	std::string name;
};

#endif /* defined (_GRAPHICSENGINE_H_) */