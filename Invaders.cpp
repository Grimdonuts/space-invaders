#include "Invaders.h"
#include "TextureManager.h"

Invaders::Invaders(){}
Invaders::~Invaders(){}

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

void Invaders::AnimateInvaders()
{
	src.x = src.w * static_cast<int>((SDL_GetTicks() / 300) % 2);
}