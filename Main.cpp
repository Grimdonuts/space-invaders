#include "Game.h"
#include <SDL_video.h>
#include <iostream>
#include <ctime>
#include "Timer.h"

int main(int argc, char* argv[]) 
{
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	Timer fpsTimer;
	Timer capTimer;
	int countedFrames = 0;
	fpsTimer.start();
	Game game;
	game.Init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

	while(game.Running())
	{
		capTimer.start();
		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if( avgFPS > 2000000 )
		{
			avgFPS = 0;
		}

		game.HandleEvents();
		game.Update();
		game.Render();
		++countedFrames;

		int frameTicks = capTimer.getTicks();
		if( avgFPS >= SCREEN_FPS && frameTicks < SCREEN_TICKS_PER_FRAME ) // this is more so if they are running too fast even with vsync on
		{
			SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
		}
	}
	
	game.Clean();

	return 0;
}