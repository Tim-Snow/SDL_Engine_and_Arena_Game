#include "Game.h"

const int FRAME_LIMIT = 60;
const double MS_PER_FRAME = 1.0 / FRAME_LIMIT;

int main(int argc, char **argv){
	Game* game = Game::instance();
	game->gfx->setTitle("Arena Game!");
	game->pushState(&TitleState::instance());

	double lastTime = SDL_GetTicks();
	
	while (game->core.isRunning()){

		double currentTime = SDL_GetTicks();
		double elapsedTime = currentTime - lastTime;

		if (elapsedTime >= MS_PER_FRAME){
			game->handleEvent();
			game->update(elapsedTime);
		}
		
		game->draw();

		lastTime = currentTime;
	}
	return 0;
}