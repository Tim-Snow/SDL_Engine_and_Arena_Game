#ifndef CORE_H_
#define CORE_H_

#include "InputManager.h"
#include "Settings.h"
#include "GraphicsEngine.h"

#include <memory>

class Core{
public:
	Core();
	Settings gameSettings;
	std::shared_ptr<GraphicsEngine> gfxEng;
	std::shared_ptr<InputManager> theInput;

	bool isRunning();
	void exit();
private:
	int width, height;
	bool running;
};

#endif /* defined  (_CORE_H_) */