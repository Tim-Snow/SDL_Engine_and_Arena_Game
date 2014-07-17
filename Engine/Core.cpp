#include "Core.h"

Core::Core(){
	gfxEng = std::shared_ptr<GraphicsEngine>(new GraphicsEngine());
	theInput = std::shared_ptr<InputManager>(new InputManager());

	gameSettings.updateSettings();
	running = true;

	//read screen sizes from settings map set by ini file
	string w = gameSettings.settings.at("screenWidth");
	width = atoi(w.c_str());
	string h = gameSettings.settings.at("screenHeight");
	height = atoi(h.c_str());

	//minimum resolution of 640x480
	if (width < 640){ width = 640; gameSettings.settings["screenWidth"] = width; }
	if (height < 480){ height = 480; gameSettings.settings["screenHeight"] = height; }

	gfxEng->makeWindow(width, height);
}

bool Core::isRunning(){
	if (running){ running = theInput->checkQuit(); }
	return running;
}

void Core::exit(){
	running = false;
	SDL_Quit();
}

