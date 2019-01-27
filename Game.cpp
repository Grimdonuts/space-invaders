#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include "Wall.h"
#include "Invaders.h"
#include "Bulllets.h"



SDL_Renderer* Game::renderer = nullptr;

Invaders invaders[5][11];
Player player;
Wall walls[2];
std::vector<Bullets> bullets;

Timer firingCooldown;
int fired = 0;
int invadersCount = 55;
int invmodx = 0;

int wallLoop;
bool movingRight = true;

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

	invaderSpeed = 400;
	invaderMovespeed = 1;
	invmodx = 1;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	//flags = SDL_WINDOW_RESIZABLE;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		window = SDL_CreateWindow(title, x, y, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Use vsync when we can if 120 fps or higher from 120 hz , 144hz the framerate cap will take care of it.
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
	screenEdgeEnding = ((resolutionW * 0.75f));
	screenEdgeEnding += (screenEdgeEnding * 0.10f);
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
		if (keyboard_state_array[SDL_SCANCODE_SPACE] && event.type == SDL_KEYDOWN)
		{
			cmd.fire = 1;
		}
		else {
			cmd.fire = 0;
		}
		if (keyboard_state_array[SDL_SCANCODE_DOWN])
		{
			cmd.down = 1;
		}
		else {
			cmd.down = 0;
		}

		if (keyboard_state_array[SDL_SCANCODE_RIGHT])
		{
			cmd.right = 1;
		}
		else {
			cmd.right = 0;
		}
		if (keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			cmd.left = 1;
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
	if (cmd.left && player.GetPlayerDestRect().x > walls[0].GetWallDestRect().x + (walls[0].GetWallDestRect().w / 2)) { player.playerx -= 8;  }
	if (cmd.right && player.GetPlayerDestRect().x < walls[1].GetWallDestRect().x - (walls[1].GetWallDestRect().w / 2))  { player.playerx += 8; }
	if (cmd.down ) { std::cout << player.playerx << std::endl; }

	player.UpdatePlayerCoord();
	
	if (cmd.fire && !firingCooldown.isStarted() || cmd.fire &&
		bullets.size() == 0 && firingCooldown.isStarted()) { 
		
		if (!firingCooldown.isStarted())
		{
			firingCooldown.start();
		}
		else {
			firingCooldown.stop();
			firingCooldown.start();
		}

		fired = firingCooldown.getTicks();

		Bullets bullet;
		bullet.LoadBullets();
		bullet.SetBulletXY(player.GetPlayerDestRect().x + 16,player.playery - 5);

		bullets.push_back(bullet);
	}
	else if (firingCooldown.getTicks() / 1000 == 2)
	{
		firingCooldown.stop();
	}


	int y = 0;
	
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			if (!movingRight && !(invaders[j][i].GetInvaderDestRect().x > screenEdgeBeginning + 64))
			 { 
				movingRight = true;
				invmodx = invaderMovespeed;
				y += 10;
			 }
				
			if (movingRight && !(invaders[j][i].GetInvaderDestRect().x < screenEdgeEnding - 32))
			{ 
				movingRight = false;
				invmodx = invaderMovespeed;
				y += 10;
			 }
		}
	}

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			invaders[j][i].AnimateInvaders(invaderSpeed);
			
			if (movingRight && static_cast<int>((SDL_GetTicks() / invaderSpeed) % 2) && !invaders[j][i].dead)
			{
				invaders[j][i].SetInvadersXY(invaders[j][i].GetInvaderDestRect().x + invmodx, invaders[j][i].GetInvaderDestRect().y + y);
			}
			else if (!movingRight && static_cast<int>((SDL_GetTicks() / invaderSpeed) % 2) && !invaders[j][i].dead) {
				invaders[j][i].SetInvadersXY(invaders[j][i].GetInvaderDestRect().x - invmodx, invaders[j][i].GetInvaderDestRect().y + y);
			}
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		//std::cout<< bullets.size() << std::endl;
		if ( bullets[i].GetBulletDestRect().y <= 0) { bullets.erase(bullets.begin() + i); }
		else if (bullets[i].hit) { bullets.erase(bullets.begin() + i); }
		else { bullets[i].SetBulletXY(bullets[i].GetBulletDestRect().x, bullets[i].GetBulletDestRect().y - 15); }

		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 11; k++)
			{
				if (bullets[i].GetBulletDestRect().x <= invaders[j][k].GetInvaderDestRect().x + (invaders[j][k].GetInvaderDestRect().w / 2) &&
				bullets[i].GetBulletDestRect().x >= invaders[j][k].GetInvaderDestRect().x - (invaders[j][k].GetInvaderDestRect().w / 2) && 
				bullets[i].GetBulletDestRect().y <= invaders[j][k].GetInvaderDestRect().y + (invaders[j][k].GetInvaderDestRect().h / 2) &&
				bullets[i].GetBulletDestRect().y >= invaders[j][k].GetInvaderDestRect().y - (invaders[j][k].GetInvaderDestRect().h / 2) &&
				!invaders[j][k].dead)
				{
					bullets[i].hit = true;
					invaders[j][k].dead = true;
					invaders[j][k].timerEnd = SDL_GetTicks() + 300;
					invadersCount--;
				}

				switch (invadersCount)
				{
					case 45:
						invaderSpeed = 395;
						invmodx = invaderMovespeed;
						invaderMovespeed = 1;
					break;
					case 35:
						invaderSpeed = 385;
						invmodx = invaderMovespeed;
						invaderMovespeed = 2;
					break;
					case 25:
						invaderSpeed = 375;
						invmodx = invaderMovespeed;
						invaderMovespeed = 2;
					break;
					case 15:
						invaderSpeed = 350;
						invmodx = invaderMovespeed;
						invaderMovespeed = 4;
					break;
					case 1:
						invaderSpeed = 300;
						invmodx = invaderMovespeed;
						invaderMovespeed = 12;
					break;
				}
			}
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
			if (!invaders[j][i].dead)
			{
				TextureManager::Draw(invaders[j][i].GetInvaderTexture(), invaders[j][i].GetInvaderSrcRect(), invaders[j][i].GetInvaderDestRect());
			}
			else if (SDL_GetTicks() < invaders[j][i].timerEnd) 
			{
				TextureManager::Draw(invaders[j][i].GetInvaderTexture(), invaders[j][i].GetInvaderSrcRect(), invaders[j][i].GetInvaderDestRect());
			}
		}
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].hit) TextureManager::Draw(bullets[i].GetBulletTexture(), bullets[i].GetBulletSrcRect(), bullets[i].GetBulletDestRect());
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
