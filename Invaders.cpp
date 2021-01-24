#include "Invaders.h"
#include "TextureManager.h"

Invaders::Invaders(){}
Invaders::~Invaders(){}

const int invaderFrames = 2;

void Invaders::LoadInvaders(int invaderType) 
{
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.w = 32;
	dest.h = 32;

	if (invaderType == 1) invader = TextureManager::LoadTexture("assets/invaders.png");
	else if (invaderType == 2) invader = TextureManager::LoadTexture("assets/invaders2.png");
	else invader = TextureManager::LoadTexture("assets/invaders3.png");
}

void Invaders::SetInvadersXY(int x, int y)
{
	dest.x = x;
	dest.y = y;
}

void Invaders::AnimateInvaders(int speed)
{
	if (!dead) src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % 2);
	else if (((SDL_GetTicks() < timerEnd)))
	{
		SDL_DestroyTexture(invader);
		invader = TextureManager::LoadTexture("assets/deadinvader.png");
		src.x = 0;
	}
}