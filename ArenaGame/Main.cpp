#include "../Engine\Core.h"
#include "Game.h"

int main(int argc, char **argv){
	Core core;
	Game game;
	std::shared_ptr<GraphicsEngine> gfx = core.gfxEng;
	std::shared_ptr<InputManager> input  = core.theInput;

	gfx->setTitle("Arena Game!");



	while (core.isRunning()){
			input->pollEvent();
			gfx->clearDisplay();

			for (auto i : game.gameObjects){
				gfx->draw(i);
			}

			gfx->updateDisplay();	
					
			if (input->isPressed(SDLK_ESCAPE)){
				core.exit();
			}
		}
	return 0;
}