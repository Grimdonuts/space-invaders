#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include "Wall.h"
#include "Invaders.h"
#include "Bulllets.h"
#include <stdlib.h>


SDL_Renderer* Game::renderer = nullptr;

Invaders invaders[55];
Player player;
Player playerLivesDisplay[3];
Wall walls[2];
std::vector<Bullets> bullets;
std::vector<Bullets> invaderBullets;
std::vector<Invaders> aliveInvaders;


Timer firingCooldown;
int fired = 0;
int invadersCount = 55;
int invmodx = 0;
int invmody = 0;

int wallLoop;
bool movingRight = true;

Game::Game()
{}
Game::~Game()
{}

void Game::Init(int width, int height)
{
	player.hit = false;
	player.playerLives = 3;
	bullets.clear();
	invaderBullets.clear();
	aliveInvaders.clear();

	fired = 0;
	invadersCount = 55;
	invmodx = 0;
	invmody = 0;

	wallLoop = 0;
	movingRight = true;

	resolutionW = width;
	resolutionH = height;
	wallLoop = (resolutionH / 32);

	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}

	invaderSpeed = 400;
	invaderMovespeed = 1;
	//invmodx = 1;

	
	player.LoadPlayer();
	player.playerx = (resolutionW / 2) - (player.GetPlayerDestRect().w / 2);
	player.playery = resolutionH * 0.85f;

	playerLivesDisplay[0].LoadPlayer();
	playerLivesDisplay[0].SetPlayerLivesCoord( 330, resolutionH * 0.96f, 16, 16);
	playerLivesDisplay[1].LoadPlayer();
	playerLivesDisplay[1].SetPlayerLivesCoord( 310, resolutionH * 0.96f, 16, 16);
	playerLivesDisplay[2].LoadPlayer();
	playerLivesDisplay[2].SetPlayerLivesCoord( 290, resolutionH * 0.96f, 16, 16);

	screenEdgeBeginning = (resolutionW * 0.25f) / 2;
	screenEdgeEnding = ((resolutionW * 0.75f));
	screenEdgeEnding += (screenEdgeEnding * 0.10f);
	Wall firstWall;
	firstWall.LoadWall(screenEdgeBeginning, 0, (resolutionH / 64));
	walls[0] = firstWall;
	Wall secondWall;
	secondWall.LoadWall(screenEdgeEnding, 0, (resolutionH / 64));
	walls[1] = secondWall;

	for (int i = 0; i < 55; i++)
	{
		Invaders invader;
		if (i % 5 < 1) invader.LoadInvaders(2);
		else if(i % 5 < 3) invader.LoadInvaders(1);
		else invader.LoadInvaders(3);
		
		// 29% to more or less get them centered with the board
		invader.SetInvadersXY((resolutionW * 0.29f) + ((i % 11) * 50), (resolutionH * 0.05) + ((i % 5) * 50)); // 50 here because 64 is too spacey and 32 is too close
		
		invaders[i] = invader;
	}

}

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_KEYDOWN && !player.hit || event.type == SDL_KEYUP && !player.hit)
	{
		if (keyboard_state_array[SDL_SCANCODE_SPACE])
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
	if (!player.hit && cmd.left && player.GetPlayerDestRect().x > walls[0].GetWallDestRect().x + (walls[0].GetWallDestRect().w / 2)) { player.playerx -= 8;  }
	if (!player.hit && cmd.right && player.GetPlayerDestRect().x < walls[1].GetWallDestRect().x - (walls[1].GetWallDestRect().w / 2))  { player.playerx += 8; }
	if (cmd.down ) { std::cout << player.playerx << std::endl; }

	player.UpdatePlayerCoord();
	
	if (!player.hit && cmd.fire && !firingCooldown.isStarted() || cmd.fire &&
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

	// keep movement and collision in their own loops so that it is consistent throughout. One bug when combining them is one row of invaders might shift off center
	for (int i = 0; i < 55; i++)
	{
		invaders[i].AnimateInvaders(invaderSpeed);
		
		if (movingRight && static_cast<int>((SDL_GetTicks() / invaderSpeed) % 2) && !invaders[i].dead)
		{
			invaders[i].SetInvadersXY(invaders[i].GetInvaderDestRect().x  + invaders[i].invadermodx , invaders[i].GetInvaderDestRect().y + invaders[i].invadermody);
			invaders[i].invadermody = 0;
		}
		else if (!movingRight && static_cast<int>((SDL_GetTicks() / invaderSpeed) % 2) && !invaders[i].dead) {
			invaders[i].SetInvadersXY(invaders[i].GetInvaderDestRect().x  - invaders[i].invadermodx , invaders[i].GetInvaderDestRect().y + invaders[i].invadermody);
			invaders[i].invadermody = 0;
		}
	}

	aliveInvaders.clear();	
	// keep movement and collision in their own loops so that it is consistent throughout. One bug when combining them is one row of invaders might shift off center
	for (int i = 0; i < 55; i++)
	{
		
		if (!movingRight && !(invaders[i].GetInvaderDestRect().x > screenEdgeBeginning + 64) && invaders[i].invadermody != 10)
		 { 
			movingRight = true;
			for (int k = 0; k < 55; k++) {  invaders[k].invadermody += 10; invaders[k].invadermodx = invaderMovespeed; }
		 }
			
		if (movingRight && !(invaders[i].GetInvaderDestRect().x < screenEdgeEnding - 32) && invmody != 10)
		{ 
			movingRight = false;
			for (int k = 0; k < 55; k++) { invaders[k].invadermody += 10; invaders[k].invadermodx = invaderMovespeed; }
		}

		if (!invaders[i].dead) aliveInvaders.push_back(invaders[i]);
	}

	for (int j = 0; j < bullets.size(); j++)
	{
		aliveInvaders.clear();

		if ( bullets[j].GetBulletDestRect().y <= 0) { bullets.erase(bullets.begin() + j); }
		else if (bullets[j].hit) { bullets.erase(bullets.begin() + j); }
		else { bullets[j].SetBulletXY(bullets[j].GetBulletDestRect().x, bullets[j].GetBulletDestRect().y - 15); }

		for (int i = 0; i < 55; i++)
		{
			if (bullets[j].GetBulletDestRect().x <= invaders[i].GetInvaderDestRect().x + (invaders[i].GetInvaderDestRect().w / 2) &&
			bullets[j].GetBulletDestRect().x >= invaders[i].GetInvaderDestRect().x - (invaders[i].GetInvaderDestRect().w / 2) && 
			bullets[j].GetBulletDestRect().y <= invaders[i].GetInvaderDestRect().y + (invaders[i].GetInvaderDestRect().h / 2) &&
			bullets[j].GetBulletDestRect().y >= invaders[i].GetInvaderDestRect().y - (invaders[i].GetInvaderDestRect().h / 2) &&
			!invaders[i].dead)
			{
				bullets[j].hit = true;
				invaders[i].dead = true;
				invaders[i].timerEnd = SDL_GetTicks() + 300;
				invadersCount--;
			}
			if (!invaders[i].dead) aliveInvaders.push_back(invaders[i]);
		}
	}

	switch (invadersCount)
	{
		case 45:
			invaderSpeed = 395;
			invaderMovespeed = 1;
		break;
		case 35:
			invaderSpeed = 385;
			invaderMovespeed = 2;
		break;
		case 25:
			invaderSpeed = 375;
			invaderMovespeed = 2;
		break;
		case 15:
			invaderSpeed = 350;
			invaderMovespeed = 4;
		break;
		case 1:
			invaderSpeed = 300;
			invaderMovespeed = 12;
		break;
	}

	srand (SDL_GetTicks());
	int randomInv = rand() % aliveInvaders.size();

	while (invaders[randomInv].dead)
	{
		randomInv = rand() % aliveInvaders.size();
	}


	for (int i = 0; i < 55; i++)
	{
		if (invaders[randomInv].GetInvaderDestRect().x == invaders[i].GetInvaderDestRect().x && 
		invaders[randomInv].GetInvaderDestRect().y < invaders[i].GetInvaderDestRect().y && !invaders[i].dead)
		{
			randomInv = i;
		}
	}

	if (invaderBullets.size() < 4)
	{
		Bullets bullet;
		bullet.LoadBullets();
		bullet.SetBulletXY(invaders[randomInv].GetInvaderDestRect().x, invaders[randomInv].GetInvaderDestRect().y + 5);
		invaderBullets.push_back(bullet);
	}

	for (int i = 0; i < invaderBullets.size(); i++)
	{
		if (invaderBullets[i].timerEnd == 0) invaderBullets[i].timerEnd = SDL_GetTicks() + (500 * i);
		if (SDL_GetTicks() > invaderBullets[i].timerEnd)
		{
			if ( invaderBullets[i].GetBulletDestRect().y >= 720) { invaderBullets.erase(invaderBullets.begin() + i); }
			else if (invaderBullets[i].hit) { invaderBullets.erase(invaderBullets.begin() + i); }
			else { invaderBullets[i].SetBulletXY(invaderBullets[i].GetBulletDestRect().x, invaderBullets[i].GetBulletDestRect().y + 5); }
		}

		if (invaderBullets[i].GetBulletDestRect().x <= player.GetPlayerDestRect().x + (player.GetPlayerDestRect().w ) &&
			invaderBullets[i].GetBulletDestRect().x >= player.GetPlayerDestRect().x - (player.GetPlayerDestRect().w / 2) && 
			invaderBullets[i].GetBulletDestRect().y <= player.GetPlayerDestRect().y + (player.GetPlayerDestRect().h / 2) &&
			invaderBullets[i].GetBulletDestRect().y >= player.GetPlayerDestRect().y - (player.GetPlayerDestRect().h / 4))
			{
				invaderBullets[i].hit = true;
				player.hit = true;
				player.timerEnd = SDL_GetTicks() + 400;
				player.playerLives--;
			}

			if (SDL_GetTicks() > player.timerEnd) 
			{
				player.timerEnd = 0;
				player.hit = false;
			}
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	if (!player.hit)
	{
		TextureManager::Draw(player.GetPlayerTexture(), player.GetPlayerSrcRect(), player.GetPlayerDestRect());
	}
	else if (SDL_GetTicks() < player.timerEnd) 
	{
		TextureManager::Draw(player.GetPlayerDeadTexture(), player.GetPlayerSrcRect(), player.GetPlayerDestRect());
	}
	
	for (int i = 0; i < wallLoop; i++)
	{
		walls[0].SetWallY(walls[0].GetYCoord(i));
		TextureManager::Draw(walls[0].GetWallTexture(), walls[0].GetWallSrcRect(), walls[0].GetWallDestRect());
		walls[1].SetWallY(walls[1].GetYCoord(i));
		TextureManager::Draw(walls[1].GetWallTexture(), walls[1].GetWallSrcRect(), walls[1].GetWallDestRect());
	}

	for (int i = 0; i < 55; i++)
	{
		if (!invaders[i].dead)
		{
			TextureManager::Draw(invaders[i].GetInvaderTexture(), invaders[i].GetInvaderSrcRect(), invaders[i].GetInvaderDestRect());
		}
		else if (SDL_GetTicks() < invaders[i].timerEnd) 
		{
			TextureManager::Draw(invaders[i].GetInvaderTexture(), invaders[i].GetInvaderSrcRect(), invaders[i].GetInvaderDestRect());
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].hit) TextureManager::Draw(bullets[i].GetBulletTexture(), bullets[i].GetBulletSrcRect(), bullets[i].GetBulletDestRect());
	}

	for (int i = 0; i < invaderBullets.size(); i++)
	{	
		if (SDL_GetTicks() > invaderBullets[i].timerEnd && !invaderBullets[i].hit) TextureManager::Draw(invaderBullets[i].GetBulletTexture(), invaderBullets[i].GetBulletSrcRect(), invaderBullets[i].GetBulletDestRect());
	}
	
	switch (player.playerLives)
	{
		case 3:
		TextureManager::Draw(playerLivesDisplay[0].GetPlayerTexture(), playerLivesDisplay[0].GetPlayerSrcRect(), playerLivesDisplay[0].GetPlayerDestRect());
		TextureManager::Draw(playerLivesDisplay[1].GetPlayerTexture(), playerLivesDisplay[1].GetPlayerSrcRect(), playerLivesDisplay[1].GetPlayerDestRect());
		TextureManager::Draw(playerLivesDisplay[2].GetPlayerTexture(), playerLivesDisplay[2].GetPlayerSrcRect(), playerLivesDisplay[2].GetPlayerDestRect());
		break;
		case 2:
		TextureManager::Draw(playerLivesDisplay[0].GetPlayerTexture(), playerLivesDisplay[0].GetPlayerSrcRect(), playerLivesDisplay[0].GetPlayerDestRect());
		TextureManager::Draw(playerLivesDisplay[1].GetPlayerTexture(), playerLivesDisplay[1].GetPlayerSrcRect(), playerLivesDisplay[1].GetPlayerDestRect());
		break;
		case 1:
		TextureManager::Draw(playerLivesDisplay[0].GetPlayerTexture(), playerLivesDisplay[0].GetPlayerSrcRect(), playerLivesDisplay[0].GetPlayerDestRect());
		break;
		case 0:
		gameOver = true;
		break;
	}

	SDL_RenderPresent(renderer);
}

void Game::Reset() {
	SDL_DestroyTexture(walls[0].GetWallTexture());
	SDL_DestroyTexture(walls[1].GetWallTexture());
	walls[0] = {};
	walls[1] = {};
	SDL_DestroyTexture(player.GetPlayerTexture());
	for (int i = 0; i < 55; i++)
	{
		SDL_DestroyTexture(invaders[i].GetInvaderTexture());
	}
	//SDL_DestroyRenderer(renderer);
	//SDL_Quit();
}

void Game::Clean() {
	SDL_DestroyTexture(walls[0].GetWallTexture());
	SDL_DestroyTexture(walls[1].GetWallTexture());
	walls[0] = {};
	walls[1] = {};
	SDL_DestroyTexture(player.GetPlayerTexture());
	for (int i = 0; i < 55; i++)
	{
		SDL_DestroyTexture(invaders[i].GetInvaderTexture());
	}
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
