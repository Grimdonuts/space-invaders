#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include "Wall.h"
#include "Invaders.h"
#include "Bulllets.h"
#include <stdlib.h>
#include "Barrier.h"


SDL_Renderer* Game::renderer = nullptr;

Invaders invaders[5][11];
Player player;
Player playerLivesDisplay[3];
Wall walls[2];
Bullets bullets[2];
Bullets invaderBullets[3];
Barrier barriers[3][9];

int fired = 0;
int invadersCount = 55;
int invmodx = 0;
int invmody = 0;
int randomInv1 = rand() % 5;
int randomInv2 = rand() % 5;
int randomInv12 = rand() % 11;
int randomInv22 = rand() % 11;


int wallLoop;
bool movingRight = true;

Game::Game()
{}
Game::~Game()
{}

void Game::Init(int width, int height)
{
	for (int i = 0; i < 2; i++) { 
		Bullets bullet;
		bullet.LoadBullets();
		bullets[i] = bullet;
	}
	player.hit = false;
	player.playerLives = 3;
	for (int i = 0; i < 3; i++) { 
		Bullets invBullet;
		invBullet.LoadBullets();
		invaderBullets[i] = invBullet;
	}

	fired = 0;
	invadersCount = 55;
	invmodx = 0;
	invmody = 0;

	wallLoop = 0;
	movingRight = true;

	resolutionW = width;
	resolutionH = height;
	wallLoop = (resolutionH / 32);

	if (!isRunning)
	{
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			isRunning = true;
		}
		else 
		{
			isRunning = false;
		}
	}
	

	invaderSpeed = 400;
	invaderMovespeed = 1;

	
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

	int barrierStart = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			switch (i)
			{
			case 0:
				barrierStart = 390;
				break;
			case 1:
				barrierStart = 590;
				break;
			case 2:
				barrierStart = 790;
				break;
			}
			barriers[i][j].LoadBarrier(barrierStart + (j / 3) * 32, (resolutionH * 0.60f) + (j % 3) * 32 );
			barriers[i][j].shot = false;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Invaders invader;
			if (i % 5 < 1) invader.LoadInvaders(2);
			else if (i % 5 < 3) invader.LoadInvaders(1);
			else invader.LoadInvaders(3);

			// 29% to more or less get them centered with the board
			invader.SetInvadersXY((resolutionW * 0.29f) + (j * 50), (resolutionH * 0.05) + (i * 50)); // 50 here because 64 is too spacey and 32 is too close

			invaders[i][j] = invader;
		}
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
	if (!player.hit && cmd.left && player.GetPlayerDestRect().x > walls[0].GetWallDestRect().x + (walls[0].GetWallDestRect().w / 2)) { player.playerx -= 8; }
	if (!player.hit && cmd.right && player.GetPlayerDestRect().x < walls[1].GetWallDestRect().x - (walls[1].GetWallDestRect().w / 2)) { player.playerx += 8; }
	if (cmd.down) { std::cout << player.playerx << std::endl; }

	player.UpdatePlayerCoord();
	
	if (!player.hit && cmd.fire && SDL_GetTicks() > bullets[0].timerEnd || cmd.fire &&
		bullets[0].hit && SDL_GetTicks() > bullets[0].timerEnd) {

		bullets[0].timerEnd = SDL_GetTicks() + 1000;
				  
		bullets[0].LoadBullets();
		bullets[0].SetBulletXY(player.GetPlayerDestRect().x + 16, player.playery - 5);
	}
	else if (!player.hit && cmd.fire && SDL_GetTicks() > bullets[1].timerEnd && SDL_GetTicks() > (bullets[0].timerEnd - 300) || cmd.fire &&
		bullets[1].hit && SDL_GetTicks() > bullets[1].timerEnd)
	{

		bullets[1].timerEnd = SDL_GetTicks() + 1000;

		bullets[1].LoadBullets();
		bullets[1].SetBulletXY(player.GetPlayerDestRect().x + 16, player.playery - 5);
	}



	// keep movement and collision in their own loops so that it is consistent throughout. One bug when combining them is one row of invaders might shift off center
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			invaders[i][j].AnimateInvaders(invaderSpeed);

			if (movingRight && static_cast<int>((SDL_GetTicks() / invaderSpeed) % 2) && !invaders[i][j].dead)
			{
				invaders[i][j].SetInvadersXY(invaders[i][j].GetInvaderDestRect().x + invaders[i][j].invadermodx, invaders[i][j].GetInvaderDestRect().y + invaders[i][j].invadermody);
				invaders[i][j].invadermody = 0;
			}
			else if (!movingRight && static_cast<int>((SDL_GetTicks() / invaderSpeed) % 2) && !invaders[i][j].dead) {
				invaders[i][j].SetInvadersXY(invaders[i][j].GetInvaderDestRect().x - invaders[i][j].invadermodx, invaders[i][j].GetInvaderDestRect().y + invaders[i][j].invadermody);
				invaders[i][j].invadermody = 0;
			}
		}
	}

	//aliveInvaders.clear();	
	// keep movement and collision in their own loops so that it is consistent throughout. One bug when combining them is one row of invaders might shift off center
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (!movingRight && !(invaders[i][j].GetInvaderDestRect().x > screenEdgeBeginning + 64) && invaders[i][j].invadermody != 10)
			{
				movingRight = true;
				for (int k = 0; k < 5; k++) { for (int l = 0; l < 11; l++) { invaders[k][l].invadermody = 10; invaders[k][l].invadermodx = invaderMovespeed; }  }
			}

			if (movingRight && !(invaders[i][j].GetInvaderDestRect().x < screenEdgeEnding - 32) && invmody != 10)
			{
				movingRight = false;
				for (int k = 0; k < 5; k++) { for (int l = 0; l < 11; l++) { invaders[k][l].invadermody = 10; invaders[k][l].invadermodx = invaderMovespeed; }  }
			}

			//if (!invaders[i].dead) aliveInvaders.push_back(invaders[i]);
		}
	}


	for (int j = 0; j < 2; j++)
	{

		if (bullets[j].GetBulletDestRect().y <= 0) { bullets[j].Clear(); }
		else if (bullets[j].hit) { bullets[j].Clear(); }
		else if (bullets[j].GetBulletDestRect().x != 9999 && bullets[j].GetBulletDestRect().y != 9999)
		{
			bullets[j].SetBulletXY(bullets[j].GetBulletDestRect().x, bullets[j].GetBulletDestRect().y - 15);
		}

		for (int i = 0; i < 5; i++)
		{
			for (int k = 0; k < 11; k++)
			{
				if (bullets[j].GetBulletDestRect().x <= invaders[i][k].GetInvaderDestRect().x + (invaders[i][k].GetInvaderDestRect().w / 2) &&
					bullets[j].GetBulletDestRect().x >= invaders[i][k].GetInvaderDestRect().x - (invaders[i][k].GetInvaderDestRect().w / 2) &&
					bullets[j].GetBulletDestRect().y <= invaders[i][k].GetInvaderDestRect().y + (invaders[i][k].GetInvaderDestRect().h / 2) &&
					bullets[j].GetBulletDestRect().y >= invaders[i][k].GetInvaderDestRect().y - (invaders[i][k].GetInvaderDestRect().h / 2) &&
					!invaders[i][k].dead)
				{
					bullets[j].hit = true;
					invaders[i][k].dead = true;
					invaders[i][k].timerEnd = SDL_GetTicks() + 300;
					invadersCount--;
				}

				//if (!invaders[i].dead) aliveInvaders.push_back(invaders[i]);
			}
		}

		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 9; i++)
			{
				if (bullets[j].GetBulletDestRect().x <= barriers[k][i].GetBarrierDestRect().x + (barriers[k][i].GetBarrierDestRect().w/2) &&
				bullets[j].GetBulletDestRect().x >= barriers[k][i].GetBarrierDestRect().x - (barriers[k][i].GetBarrierDestRect().w /2) &&
				bullets[j].GetBulletDestRect().y <= barriers[k][i].GetBarrierDestRect().y + (barriers[k][i].GetBarrierDestRect().h/2) &&
				bullets[j].GetBulletDestRect().y >= barriers[k][i].GetBarrierDestRect().y - (barriers[k][i].GetBarrierDestRect().h/2) &&
				!barriers[k][i].shot)
				{
					bullets[j].hit = true;
					barriers[k][i].shot = true;
				}
			}
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

	randomInv1 = rand() % 5;
	randomInv2 = rand() % 5;
	randomInv12 = rand() % 11;
	randomInv22 = rand() % 11;

	if (invadersCount != 0)
	{
		while (invaders[randomInv1][randomInv12].dead)
		{
			randomInv1 = rand() % 5;
			randomInv12 = rand() % 11;
		}
	}
	if (invadersCount > 1)
	{
		while (invaders[randomInv2][randomInv22].dead)
		{
			randomInv2 = rand() % 5;
			randomInv22 = rand() % 11;
		}
	}
	

	for (int i = 0; i < 5; i++)
	{
		if (!invaders[i][randomInv12].dead)
		{
			randomInv1 = i;
		}
		if (!invaders[i][randomInv22].dead)
		{
			randomInv2 = i;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (invaders[randomInv1][randomInv12].dead) randomInv1 = -1;
		if (invaders[randomInv2][randomInv22].dead || invadersCount < 2) randomInv2 = -1;

		if (invaderBullets[i].GetBulletDestRect().x == 9999 && invaderBullets[i].GetBulletDestRect().y == 9999 && i == 0 && randomInv1 != -1)
		{
			invaderBullets[i].LoadBullets();
			invaderBullets[i].SetBulletXY(invaders[randomInv1][randomInv12].GetInvaderDestRect().x, invaders[randomInv1][randomInv12].GetInvaderDestRect().y + 5);
			invaderBullets[i].hit = false;
		}

		if (invaderBullets[i].GetBulletDestRect().x == 9999 && invaderBullets[i].GetBulletDestRect().y == 9999 && i != 0 && randomInv2 != -1)
		{
			invaderBullets[i].LoadBullets();
			invaderBullets[i].SetBulletXY(invaders[randomInv2][randomInv22].GetInvaderDestRect().x, invaders[randomInv2][randomInv22].GetInvaderDestRect().y + 5);
			invaderBullets[i].hit = false;
		}
		
	}

	for (int i = 0; i < 2; i++)
	{
		if (invaderBullets[i].timerEnd == 0) invaderBullets[i].timerEnd = SDL_GetTicks() + 100;

		if (invaderBullets[i].GetBulletDestRect().y >= 720 && invaderBullets[i].GetBulletDestRect().y != 9999) {
			invaderBullets[i].Clear();
		}
		else if (invaderBullets[i].hit) {
			invaderBullets[i].Clear();
		}
		else { invaderBullets[i].SetBulletXY(invaderBullets[i].GetBulletDestRect().x, invaderBullets[i].GetBulletDestRect().y + 5); }

		if (invaderBullets[i].GetBulletDestRect().x <= player.GetPlayerDestRect().x + (player.GetPlayerDestRect().w ) &&
			invaderBullets[i].GetBulletDestRect().x >= player.GetPlayerDestRect().x - (player.GetPlayerDestRect().w / 2) && 
			invaderBullets[i].GetBulletDestRect().y <= player.GetPlayerDestRect().y + (player.GetPlayerDestRect().h / 2) &&
			invaderBullets[i].GetBulletDestRect().y >= player.GetPlayerDestRect().y - (player.GetPlayerDestRect().h / 4))
			{
				invaderBullets[i].hit = true;
				player.hit = true;
				player.timerEnd = SDL_GetTicks() + 400;
				player.playerLives--;
				if (player.playerLives < 0) player.playerLives = 0;
			}

		if (SDL_GetTicks() > player.timerEnd) 
		{
			player.timerEnd = 0;
			player.hit = false;
		}

		for (int j = 0; j < 2; j++)
		{
			if (invaderBullets[i].GetBulletDestRect().x <= bullets[j].GetBulletDestRect().x + (bullets[j].GetBulletDestRect().w / 2) &&
				invaderBullets[i].GetBulletDestRect().x >= bullets[j].GetBulletDestRect().x - (bullets[j].GetBulletDestRect().w / 2) &&
				invaderBullets[i].GetBulletDestRect().y <= bullets[j].GetBulletDestRect().y + (bullets[j].GetBulletDestRect().h / 2) &&
				invaderBullets[i].GetBulletDestRect().y >= bullets[j].GetBulletDestRect().y - (bullets[j].GetBulletDestRect().h / 2))
			{
				invaderBullets[i].hit = true;
				bullets[j].hit = true;
			}
		}

		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (invaderBullets[i].GetBulletDestRect().x <= barriers[k][j].GetBarrierDestRect().x + (barriers[k][j].GetBarrierDestRect().w / 2) &&
				invaderBullets[i].GetBulletDestRect().x >= barriers[k][j].GetBarrierDestRect().x - (barriers[k][j].GetBarrierDestRect().w / 2) &&
				invaderBullets[i].GetBulletDestRect().y <= barriers[k][j].GetBarrierDestRect().y + (barriers[k][j].GetBarrierDestRect().h / 2) &&
				invaderBullets[i].GetBulletDestRect().y >= barriers[k][j].GetBarrierDestRect().y - (barriers[k][j].GetBarrierDestRect().h / 2) &&
				!barriers[k][j].shot)
				{
					invaderBullets[i].hit = true;
					barriers[k][j].shot = true;
				}
			}
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

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (!invaders[i][j].dead)
			{
				TextureManager::Draw(invaders[i][j].GetInvaderTexture(), invaders[i][j].GetInvaderSrcRect(), invaders[i][j].GetInvaderDestRect());
			}
			else if (SDL_GetTicks() < invaders[i][j].timerEnd)
			{
				TextureManager::Draw(invaders[i][j].GetInvaderTexture(), invaders[i][j].GetInvaderSrcRect(), invaders[i][j].GetInvaderDestRect());
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (!bullets[i].hit) TextureManager::Draw(bullets[i].GetBulletTexture(), bullets[i].GetBulletSrcRect(), bullets[i].GetBulletDestRect());
	}

	for (int i = 0; i < 2; i++)
	{	
		if (!invaderBullets[i].hit) 
		{
			if (i == 0 && invadersCount != 0)
			{
				TextureManager::Draw(invaderBullets[i].GetBulletTexture(), invaderBullets[i].GetBulletSrcRect(), invaderBullets[i].GetBulletDestRect());
			}

			if (i == 1 && invadersCount > 1)
			{
				TextureManager::Draw(invaderBullets[i].GetBulletTexture(), invaderBullets[i].GetBulletSrcRect(), invaderBullets[i].GetBulletDestRect());
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (!barriers[i][j].shot) 
			{
				TextureManager::Draw(barriers[i][j].GetBarrierTexture(), barriers[i][j].GetBarrierSrcRect(), barriers[i][j].GetBarrierDestRect());
			}
		}
	}

	if (invadersCount <= 0) player.playerLives = 0; // add a victory screen sometime
	
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
		case 0: // add a gameover screen sometime
		SDL_DestroyTexture(walls[0].GetWallTexture());
		SDL_DestroyTexture(walls[1].GetWallTexture());
		walls[0] = {};
		walls[1] = {};
		SDL_DestroyTexture(player.GetPlayerTexture());
		SDL_DestroyTexture(player.GetPlayerDeadTexture());
		SDL_DestroyTexture(playerLivesDisplay[0].GetPlayerTexture());
		SDL_DestroyTexture(playerLivesDisplay[0].GetPlayerDeadTexture());
		SDL_DestroyTexture(playerLivesDisplay[1].GetPlayerTexture());
		SDL_DestroyTexture(playerLivesDisplay[1].GetPlayerDeadTexture());
		SDL_DestroyTexture(playerLivesDisplay[2].GetPlayerTexture());
		SDL_DestroyTexture(playerLivesDisplay[2].GetPlayerDeadTexture());
		for (int i = 0; i < 2; i++)
		{
			SDL_DestroyTexture(bullets[i].GetBulletTexture());
		}
		

		for (int i = 0; i < 2; i++)
		{
			SDL_DestroyTexture(invaderBullets[i].GetBulletTexture());	
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				SDL_DestroyTexture(invaders[i][j].GetInvaderTexture());
			}
		}

		for (int i =0; i < 3; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				SDL_DestroyTexture(barriers[i][j].GetBarrierTexture());
			}
		}
		gameOver = true;
		break;
	}

	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(bullets[i].GetBulletTexture());
	}
	SDL_DestroyTexture(walls[0].GetWallTexture());
	SDL_DestroyTexture(walls[1].GetWallTexture());
	walls[0] = {};
	walls[1] = {};
	SDL_DestroyTexture(player.GetPlayerTexture());
	SDL_DestroyTexture(player.GetPlayerDeadTexture());
	SDL_DestroyTexture(playerLivesDisplay[0].GetPlayerTexture());
	SDL_DestroyTexture(playerLivesDisplay[0].GetPlayerDeadTexture());
	SDL_DestroyTexture(playerLivesDisplay[1].GetPlayerTexture());
	SDL_DestroyTexture(playerLivesDisplay[1].GetPlayerDeadTexture());
	SDL_DestroyTexture(playerLivesDisplay[2].GetPlayerTexture());
	SDL_DestroyTexture(playerLivesDisplay[2].GetPlayerDeadTexture());
	
	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(invaderBullets[i].GetBulletTexture());	
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			SDL_DestroyTexture(invaders[i][j].GetInvaderTexture());
		}
	}
	for (int i =0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			SDL_DestroyTexture(barriers[i][j].GetBarrierTexture());
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
