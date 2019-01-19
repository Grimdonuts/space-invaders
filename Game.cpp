#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
GameObjects* player;
GameObjects* map;
input_cmd cmd = {};

Game::Game()
{}
Game::~Game()
{}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
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

	player = new GameObjects();
	map = new GameObjects(2, 300);
}

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		if (keyboard_state_array[SDL_SCANCODE_UP])
		{
			cmd.up = 1;
			//std::cout << "up" << std::endl;
		}
		else {
			cmd.up = 0;
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
	player->Update(cmd);
	map->MoveInvaders();
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	player->LoadPlayer();
	map->DrawInvaders();
	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	delete player;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
