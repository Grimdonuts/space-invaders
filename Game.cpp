#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include "Wall.h"
#include "Invaders.h"


SDL_Renderer* Game::renderer = nullptr;

Invaders invaders[5][11];
Player player;
Wall walls[2];
int wallLoop;

Game::Game()
{}
Game::~Game()
{}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	resolutionW = width;
	resolutionH = height;
	wallLoop = (resolutionH / 32);
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	//flags = SDL_WINDOW_RESIZABLE;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		window = SDL_CreateWindow(title, x, y, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	player.LoadPlayer();
	player.playerx = (resolutionW / 2) - (player.GetPlayerDestRect().w / 2);
	player.playery = resolutionH * 0.85f;

	screenEdgeBeginning = (resolutionW * 0.25f) / 2;
	screenEdgeEnding = ((resolutionW * 0.75f) + screenEdgeBeginning);
	Wall firstWall;
	firstWall.LoadWall(screenEdgeBeginning, 0, (resolutionH / 64));
	walls[0] = firstWall;
	Wall secondWall;
	secondWall.LoadWall(screenEdgeEnding, 0, (resolutionH / 64));
	walls[1] = secondWall;

for (int j = 0; j < 5; j++)
{
	for (int i = 0; i < 11; i++)
	{
		Invaders invader;
		if (j < 1) invader.LoadInvaders(2);
		else if(j <= 2) invader.LoadInvaders(1);
		else invader.LoadInvaders(3);
		
		// 29% to more or less get them centered with the board
		invader.SetInvadersXY((resolutionW * 0.29f) + (i * 50), (resolutionH * 0.05) + (j * 50)); // 50 here because 64 is too spacey and 32 is too close
		
		invaders[j][i] = invader;
	}
}
}

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		if (keyboard_state_array[SDL_SCANCODE_SPACE])
		{
			cmd.fire = 1;
			//std::cout << "up" << std::endl;
		}
		else {
			cmd.fire = 0;
		}
		if (keyboard_state_array[SDL_SCANCODE_DOWN])
		{
			cmd.down = 1;
			//std::cout << "down" << std::endl;
		}
		else {
			cmd.down = 0;
		}

		if (keyboard_state_array[SDL_SCANCODE_RIGHT])
		{
			cmd.right = 1;
			//std::cout << "right" << std::endl;
		}
		else {
			cmd.right = 0;
		}
		if (keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			cmd.left = 1;
			//std::cout << "left" << std::endl;
		}
		else {
			cmd.left = 0;
		}
	}

	switch(event.type)
	{
		case SDL_QUIT:
		{
			isRunning = false;
		} break;
	}
}

void Game::Update()
{
	if (cmd.left && player.GetPlayerDestRect().x > walls[0].GetWallDestRect().x + (walls[0].GetWallDestRect().w / 2)) { player.playerx -= 8; std::cout << player.playerx << std::endl; }
	if (cmd.right && player.GetPlayerDestRect().x < walls[1].GetWallDestRect().x - (walls[1].GetWallDestRect().w / 2))  { player.playerx += 8; std::cout << player.playerx << std::endl; }
	if (cmd.down /*&& dest.x <= (wall2Dest.x - wall2Dest.w)*/) { std::cout << player.playerx << std::endl; }
	player.UpdatePlayerCoord();
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			invaders[j][i].AnimateInvaders();
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	TextureManager::Draw(player.GetPlayerTexture(), player.GetPlayerSrcRect(), player.GetPlayerDestRect());
	for (int i = 0; i < wallLoop; i++)
	{
		walls[0].SetWallY(walls[0].GetYCoord(i));
		TextureManager::Draw(walls[0].GetWallTexture(), walls[0].GetWallSrcRect(), walls[0].GetWallDestRect());
		walls[1].SetWallY(walls[1].GetYCoord(i));
		TextureManager::Draw(walls[1].GetWallTexture(), walls[1].GetWallSrcRect(), walls[1].GetWallDestRect());
	}

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			TextureManager::Draw(invaders[j][i].GetInvaderTexture(), invaders[j][i].GetInvaderSrcRect(), invaders[j][i].GetInvaderDestRect());
		}
	}
	
	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	SDL_DestroyTexture(walls[0].GetWallTexture());
	SDL_DestroyTexture(walls[1].GetWallTexture());
	walls[0] = {};
	walls[1] = {};
	SDL_DestroyTexture(player.GetPlayerTexture());
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			SDL_DestroyTexture(invaders[j][i].GetInvaderTexture());
		}
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
