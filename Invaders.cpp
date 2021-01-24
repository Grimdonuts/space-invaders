#include "Invaders.h"
#include "TextureManager.h"

Invaders::Invaders(){}
Invaders::~Invaders(){}

const int invaderFrames = 2;

void Invaders::LoadInvaders() 
{
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.w = 32;
	dest.h = 32;
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
		src.x = 0;
	}
}