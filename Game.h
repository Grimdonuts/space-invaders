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
	void MenuScreen(int width, int height);
	void MenuRender();
	void HandleMenuEvents(bool delayInput);
	void MenuUpdate();
	void MenuClean();
	void Init(int width, int height);
	int invaderSpeed;
	int invaderMovespeed;
	bool gameOver = false;
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running() { return isRunning; };
	bool InMenu() { return isInMenu; };
	static SDL_Renderer* renderer;
private:
	float resolutionW = 0;
	float resolutionH = 0;
	float screenEdgeBeginning = 0;
	float screenEdgeEnding = 0;
	bool isRunning;
	bool isInMenu;
	int count = 0;
	int movement = 9;
};

