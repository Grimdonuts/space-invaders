#include "Game.h"
#include <SDL_video.h>
#include <iostream>
#include <ctime>
#include "Timer.h"
#undef main

int main(int argc, char *argv[])
{
	SDL_Window *window = NULL;
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	Timer fpsTimer;
	Timer capTimer;
	int countedFrames = 0;
	fpsTimer.start();
	Game game;
	srand(SDL_GetTicks());
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

		game.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Use vsync when we can if 120 fps or higher from 120 hz , 144hz the framerate cap will take care of it.
	}

	game.MenuScreen(1280, 720);

	while (game.Running())
	{
		capTimer.start();
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		if (game.InMenu())
		{
			game.HandleMenuEvents(game.gameOver);
			game.MenuUpdate();
			game.MenuRender();
			if (game.gameOver)
			{
				SDL_Delay(500);
				game.gameOver = false;
			}
		}
		else
		{
			game.HandleEvents();
			game.Update();
			game.Render();

			if (game.gameOver)
			{
				game.MenuScreen(1280, 720);
			}
		}

		++countedFrames;
		int frameTicks = capTimer.getTicks();
		if (avgFPS >= SCREEN_FPS && frameTicks < SCREEN_TICKS_PER_FRAME) // this is more so if they are running too fast even with vsync on
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	capTimer.stop();
	fpsTimer.stop();
	if (game.InMenu())
	{
		game.MenuClean();
	}
	else
	{
		game.Clean();
	}

	SDL_DestroyWindow(window);

	return 0;
}