#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Timer.h"

struct input_cmd{
    uint32_t up:1;
    uint32_t down:1;
    uint32_t right:1;
    uint32_t left:1;
    uint32_t fire:1;
    uint32_t bomb:1;
};

class Game {
public:
	Game();
	~Game();

	input_cmd cmd = {};
	//void MenuScreen();
	void Init( int width, int height);
	int invaderSpeed;
	int invaderMovespeed;
	bool gameOver = false;
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running() { return isRunning; };
	static SDL_Renderer* renderer;
private:
	float resolutionW;
	float resolutionH;
	int screenEdgeBeginning;
	int screenEdgeEnding;
	bool isRunning;
	int count = 0;
	int movement = 9;
};

