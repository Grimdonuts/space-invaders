#include "GameObjects.h"
#include "TextureManager.h"
#include <iostream>

int boardLayout[22][29] = {
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1},//1
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1},//2
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1},//3
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1},//4
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1},//5
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1},//6
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//7
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//8
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//9
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//10
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//11
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//12
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//13
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//14
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//15
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//16
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//17
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//18
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//19
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//20
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//21
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}//22
};

GameObjects::GameObjects()
{
	animated = false;

	player = TextureManager::LoadTexture("assets/tank.png");

	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.x = 0;
	dest.y = 0;

	LoadPlayer();
}

GameObjects::GameObjects(int invFrames, int invSpeed)
{
	animated = true;
	frames = invFrames;
	speed = invSpeed;

	invaders1 = TextureManager::LoadTexture("assets/invaders.png");

	invSrc.x = 0;
	invSrc.y = 0;
	invSrc.h = 32;
	invSrc.w = 32;
	
	invDest.x = 0;
	invDest.y = 0;

	LoadInvaders(boardLayout);
}

void GameObjects::LoadInvaders(int arr[22][29])
{
	invDest.h = 32;
	invDest.w = 32;

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}


void GameObjects::DrawInvaders()
{
	invDest.x = 0;
	invDest.y = 0;
	int type = 0;

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			type = map[i][j];

			invDest.x = 161 +  (j * 32) + movements;
			invDest.y = i * 32;

			switch(type)
			{
				case 0:
				break;
				case 1:
					TextureManager::Draw(invaders1, invSrc, invDest);
				break;
				case 2:

				break;
			}
		}
	}
	if (static_cast<int>((SDL_GetTicks() / speed) % frames) && movingRight) movements++;
	else if (static_cast<int>((SDL_GetTicks() / speed) % frames) && !movingRight) movements--;

	if (movements == 100) { movingRight = false; }
	if (movements == -100) { movingRight = true; }
}

void GameObjects::MoveInvaders()
{
	if (animated)
	{
		invSrc.x = invSrc.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	//	std::cout << static_cast<int>((SDL_GetTicks() / speed) % frames) << std::endl;
	}

	// if (invDest.x >= 0)
	// {
	// 	invadersx += 8;
	// 	invDest.x = invadersx;
	// 	//dest.y = playery;
	// 	std::cout << invadersx << std::endl;

	// } 
	//if (dest.x < 987) dest.x += 8;
	// int type = 0;

	// for (int i = 0; i < 25; i++)
	// {
	// 	for (int j = 0; j < 40; j++)
	// 	{
	// 		if (map[i][j] == 2) map[i][j] = 1;
	// 		else if (map[i][j] == 1) map[i][j] = 2;

	// 		type = map[i][j];

	// 		dest.x = j * 32;
	// 		dest.y = i * 32;

	// 		switch(type)
	// 		{
	// 			case 0:
	// 			break;
	// 			case 1:
	// 				TextureManager::Draw(invaders1, src, dest);
	// 			break;
	// 		}
	// 	}
	// }
}

void GameObjects::Update(input_cmd cmd) {


	//std::cout << playerx << std::endl;
	if (cmd.left && playerx > 200) playerx -= 8;
	if (cmd.right && playerx < 987) playerx += 8;
	//if (cmd.up) playery -= 10;
	//if (cmd.down) playery +=  10;

		
	src.h = 32;
	src.w = 32;
	src.x = 0;
	src.y = 0;

	dest.x = playerx;
	dest.y = playery;
	dest.w = src.w * 2;
	dest.h = src.h * 2;
}

void GameObjects::LoadPlayer() {
	TextureManager::Draw(player, src, dest);
}

GameObjects::~GameObjects()
{}

