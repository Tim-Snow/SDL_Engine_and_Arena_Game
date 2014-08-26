#include "Core.h"

Core::Core(): running(true){
	gfxEng = std::shared_ptr<GraphicsEngine>(new GraphicsEngine());

	Settings::instance().updateSettings();

	//read screen sizes from settings map set by ini file
	std::string w = Settings::instance().getSetting("screenWidth");
	width = atoi(w.c_str());
	std::string h = Settings::instance().getSetting("screenHeight");
	height = atoi(h.c_str());
	std::string fs = Settings::instance().getSetting("fullscreen");
	if (fs == "true"){ fullscreen = true; } 
	else			 { fullscreen = false;}

	//minimum resolution of 640x360 (16:9)
	if (width  < 640){ width  = 640; Settings::instance().setSetting("screenWidth" , width ); }
	if (height < 360){ height = 360; Settings::instance().setSetting("screenHeight", height); }

	gfxEng->makeWindow(width, height, fullscreen);
}

bool Core::isRunning(){
	if (running){ running = theInput->checkQuit(); }
	return running;
}

void Core::exit(){
	running = false;
	SDL_Quit();
}

