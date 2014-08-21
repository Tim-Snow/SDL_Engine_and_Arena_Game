#include "Game.h"

const int FRAME_LIMIT = 60;
const float MS_PER_FRAME = 1000.0 / FRAME_LIMIT;

int main(int argc, char **argv){
	Game game;
	int fps = 0;
	int elapsedTime, currentTime = 0;
	int fpsOutTimer = SDL_GetTicks();
	int lastTime = SDL_GetTicks();
	
	while (game.core.isRunning()){
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastTime;

		if (elapsedTime >= MS_PER_FRAME){
			game.handleEvent();
			game.update(elapsedTime);
			game.draw();
			++fps;
		} else {
			while (SDL_GetTicks() - currentTime < MS_PER_FRAME){
				SDL_Delay(1);
			}
		}

		if ((currentTime - fpsOutTimer) >= 1000){ // 1 second has passed
			game.gfx->setTitle("Arena Game! FPS: " + std::to_string(fps));
			fpsOutTimer = SDL_GetTicks();
			fps = 0;
		}

		lastTime = currentTime;
	}
	return 0;
}