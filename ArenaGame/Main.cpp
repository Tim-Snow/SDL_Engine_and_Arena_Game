#include "Game.h"

int main(int argc, char **argv){
	Game game;
	game.gfx->setTitle("Arena Game!");

	while (game.core.isRunning()){
		game.input->pollEvent();
		game.gfx->clearDisplay();

		for (auto i : game.gameObjects){
			if (i.getVisible()){	
				game.gfx->draw(&i); 
			}
		}

		game.gfx->updateDisplay();
		if (game.input->isPressed(SDLK_SPACE)){ game.gameObjects[0].move(); }
		if (game.input->isPressed(SDLK_ESCAPE)){ game.core.exit(); }
	}
	return 0;
}