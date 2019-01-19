#include "Game.h"
#include <SDL_video.h>

int main(int argc, char* argv[]) {

	const float FPS = 60;
	const float frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game game;
	game.Init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

	while(game.Running())
	{

		frameStart = SDL_GetTicks();

		game.HandleEvents();
		game.Update();
		game.Render();

		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	game.Clean();

	return 0;
}