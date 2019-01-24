#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include "Wall.h"


SDL_Renderer* Game::renderer = nullptr;
Player* player;
std::vector<Wall*> walls;

Game::Game()
{}
Game::~Game()
{}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	resolutionW = width;
	resolutionH = height;

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

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

	player = new Player();
	player->LoadPlayer();

	screenEdgeBeginning = (resolutionW * 0.25f) / 2;
	screenEdgeEnding = ((resolutionW * 0.75f) + screenEdgeBeginning);
	Wall* firstWall;
	firstWall = new Wall();
	firstWall->LoadWall(screenEdgeBeginning, 0);
	walls.push_back(firstWall);
	Wall* secondWall = new Wall();
	secondWall->LoadWall(screenEdgeEnding, 0);
	walls.push_back(secondWall);

	//map = new GameObjects(2, 300);
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
	if (cmd.left && player->GetPlayerDestRect().x > walls[0]->GetWallDestRect().x + (walls[0]->GetWallDestRect().w / 2)) { player->playerx -= 8; std::cout << player->playerx << std::endl; }
	if (cmd.right && player->GetPlayerDestRect().x < walls[1]->GetWallDestRect().x - (walls[1]->GetWallDestRect().w / 2))  { player->playerx += 8; std::cout << player->playerx << std::endl; }
	if (cmd.down /*&& dest.x <= (wall2Dest.x - wall2Dest.w)*/) { std::cout << player->playerx << std::endl; }
	player->UpdatePlayerCoord();
	//map->MoveInvaders();
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	TextureManager::Draw(player->GetPlayerTexture(), player->GetPlayerSrcRect(), player->GetPlayerDestRect());
	for (int i = 0; i < 22; i++)
	{
		walls[0]->SetWallY(walls[0]->GetYCoord(i));
		TextureManager::Draw(walls[0]->GetWallTexture(), walls[0]->GetWallSrcRect(), walls[0]->GetWallDestRect());
		walls[1]->SetWallY(walls[1]->GetYCoord(i));
		TextureManager::Draw(walls[1]->GetWallTexture(), walls[1]->GetWallSrcRect(), walls[1]->GetWallDestRect());
	}
	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	walls.clear();
	delete player;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
