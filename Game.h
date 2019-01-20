#pragma once

#include <SDL.h>
#include <cstdint>
#include "GameObjects.h"
#include <ctime>


class Game {
public:
	Game();
	~Game();

	void Init(const char* title, int x, int y, int width, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running() { return isRunning; };

	static SDL_Renderer* renderer;
private:

	long gameTime;
	bool isRunning;
	SDL_Window* window;
	int count = 0;
	int movement = 9;
};

