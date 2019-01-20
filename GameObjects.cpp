#include "GameObjects.h"
#include "TextureManager.h"
#include <iostream>

int boardLayout[22][29] = {
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//1
	{10,0,0,0,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,0,0,0,11},//2
	{10,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,11},//3
	{10,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,11},//4
	{10,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,11},//5
	{10,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,11},//6
	{10,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,11},//7
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//8
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//9
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//10
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//11
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//12
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//13
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//14
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//15
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//16
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//17
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//18
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//19
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//20
	{10,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11},//21
	{10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11}//22
};

GameObjects::GameObjects(int invFrames, int invSpeed)
{
	animated = true;
	frames = invFrames;
	speed = invSpeed;

	invaders1 = TextureManager::LoadTexture("assets/invaders.png");
	invaders2 = TextureManager::LoadTexture("assets/invaders2.png");
	player = TextureManager::LoadTexture("assets/tank.png");
	wall = TextureManager::LoadTexture("assets/wall.png");
	bullet = TextureManager::LoadTexture("assets/bullet.png");

	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.x = 0;
	dest.y = 0;

	invSrc.x = 0;
	invSrc.y = 0;
	invSrc.h = 32;
	invSrc.w = 32;
	
	invDest.x = 0;
	invDest.y = 0;

	firstinvSrc.x = 0;
	firstinvSrc.y = 0;
	firstinvSrc.h = 32;
	firstinvSrc.w = 32;

	firstinvDest.x = 0;
	firstinvDest.y = 0;
	firstinvDest.h = 32;
	firstinvDest.w = 32;

	wallSrc.x = 0;
	wallSrc.y = 0;
	wallSrc.h = 32;
	wallSrc.w = 32;
	
	wallDest.w = wallSrc.w * 2;
	wallDest.h = wallSrc.h * 2;;
	wallDest.x = 0;
	wallDest.y = 0;

	wall2Src.x = 0;
	wall2Src.y = 0;
	wall2Src.h = 32;
	wall2Src.w = 32;
	
	wall2Dest.w = wall2Src.w * 2;
	wall2Dest.h = wall2Src.h * 2;;
	wall2Dest.x = 0;
	wall2Dest.y = 0;

	bullSrc.x = 0;
	bullSrc.y = 0;
	bullSrc.h = 32;
	bullSrc.w = 32;

	bullDest.x = 0;
	bullDest.y = 0;
	bullDest.w = 32;
	bullDest.h = 32;

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

			switch(type)
			{
				case 0:
				break;
				case 1:
					invDest.x = 161 +  (j * 32) + invadersx;
					invDest.y = (i * 32) + invadersy;
					TextureManager::Draw(invaders1, invSrc, invDest);
				break;
				case 2:
					firstinvDest.x = 161 +  (6 * 32) + invadersx;
					firstinvDest.y = (2 * 32) + invadersy;
					if ((firstinvDest.x + invadersx) <= 225) firstinvDest.x = 225;

					invDest.x = 161 +  (j * 32) + invadersx;
					invDest.y = (i * 32) + invadersy;
					TextureManager::Draw(invaders2, invSrc, invDest);
				break;
				case 5:
				break;
				case 9:
					if (playerx == 0 && playery == 0)
					{
						playerx = 161 + (j*32);
						playery = (i*32);
					}
					dest.x = playerx;
					dest.y = playery;
					TextureManager::Draw(player, src, dest);
				break;
				case 10:
					wallDest.x = 161 + (j * 32);
					wallDest.y = (i * 32);
					TextureManager::Draw(wall, wallSrc, wallDest);
				break;
				case 11:
					wall2Dest.x = 161 + (j * 32);
					wall2Dest.y = (i * 32);
					TextureManager::Draw(wall, wall2Src, wall2Dest);
				break;
			}
		}
	}
	TextureManager::Draw(bullet, bullSrc, bullDest);
}

void GameObjects::MoveInvaders()
{
	if (animated)
	{
		invSrc.x = invSrc.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		if (static_cast<int>((SDL_GetTicks() / speed) % frames) && movingRight) invadersx += 1;
		else if (static_cast<int>((SDL_GetTicks() / speed) % frames) && !movingRight) invadersx -= 1;

		if (invDest.x != 0)
		{
			 if (static_cast<int>((SDL_GetTicks() / speed) % frames) && (invDest.x + invadersx) >= (wall2Dest.x + (wall2Dest.w / 2)) && movingRight) { movingRight = false; 
				invadersy += 10;
			  }
			 if ( static_cast<int>((SDL_GetTicks() / speed) % frames) && (firstinvDest.x + invadersx) <= (wallDest.x + (wallDest.w / 2)) && !movingRight) { movingRight = true;
				invadersy += 10;
			}
		}

	}
}

void GameObjects::DrawBullets(input_cmd cmd)
{
	if (cmd.fire)
	{
		bullDest.x = playerx;
		bullDest.y = playery + 10;
		bullDest.h = 32;
		bullDest.w = 32;
		TextureManager::Draw(bullet, bullSrc, bullDest);
	}
	else
	{
		bullDest.y -= 1;
		TextureManager::Draw(bullet, bullSrc, bullDest);
	}
}

void GameObjects::Update(input_cmd cmd) {

	if (cmd.left && dest.x >= (wallDest.x + wallDest.w)) playerx -= 8;
	if (cmd.right && dest.x <= (wall2Dest.x - wall2Dest.w)) playerx += 8;
	if (cmd.fire) 
	{
		GameObjects::DrawBullets(cmd);
	}
	else if (bullDest.y != 0)
	{
		GameObjects::DrawBullets(cmd);
	}
		
	src.h = 32;
	src.w = 32;
	src.x = 0;
	src.y = 0;

	dest.x = playerx;
	dest.y = playery;
	dest.w = src.w * 2;
	dest.h = src.h * 2;
}

GameObjects::~GameObjects()
{}

