#include "Game.h"
#include <Windows.h>

const int FRAME_LIMIT = 60;
const double MS_PER_FRAME = 1.0 / FRAME_LIMIT;

int main(int argc, char **argv){
	Game game;
	game.gfx->setTitle("Arena Game!");

	double lastTime = GetTickCount();
	while (game.core.isRunning()){
		double currentTime = GetTickCount();
		double elapsedTime = currentTime - lastTime;

		game.input->pollEvent();

		if (elapsedTime >= MS_PER_FRAME){
			game.update(elapsedTime);
		}
		game.draw();

		lastTime = currentTime;
	}
	return 0;
}