#include "../Engine\Core.h"

int main(int argc, char **argv){
	Core core;
	core.setTitle("Arena Game!");

	if (core.initialize() == true){
		//Init was successful, start game
		core.mainLoop();
	}
	return 0;
}