#include "../Engine\Core.h"

int main(int argc, char **argv){
	Core core;
	std::shared_ptr<GraphicsEngine> gfx = core.gfxEng;
	std::shared_ptr<InputManager> input  = core.theInput;
	
	gfx->setTitle("Arena Game!");

	while (core.isRunning()){
			input->pollEvent();
			gfx->clearDisplay();

			gfx->updateDisplay();
					
			if (input->isPressed(SDLK_ESCAPE)){
				core.exit();
			}
		}
	return 0;
}