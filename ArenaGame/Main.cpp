#include "../Engine\Core.h"

int main(int argc, char **argv){
	Core core;
	core.setTitle("Arena Game!");

	if (core.initialize()){
		//Init was successful, start game
		while (core.isRunning()){
			core.updateInput();
			core.updateDisplay();
		}
	}
	return 0;
}