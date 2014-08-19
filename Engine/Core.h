#ifndef CORE_H_
#define CORE_H_

#include "InputManager.h"
#include "Settings.h"
#include "GraphicsEngine.h"

#include <memory>

class Core{
public:
	Core();

	std::shared_ptr<GraphicsEngine> gfxEng;
	std::shared_ptr<InputManager> theInput;

	bool isRunning();
	void exit();
private:
	

	int width, height;
	bool running;

	Settings gameSettings;
};

#endif /* defined  (_CORE_H_) */