#include "Bulllets.h"
#include "TextureManager.h"

Bullets::Bullets(){
}
Bullets::~Bullets(){}

void Bullets::LoadBullets() 
{
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.w = 32;
	dest.h = 32;
	dest.y = 9999;
	dest.x = 9999;

	bullet = TextureManager::LoadTexture("assets/bullet.png");
}

void Bullets::SetBulletXY(int x, int y)
{
	dest.x = x;
	dest.y = y;
}

void Bullets::Clear()
{
	dest.y = 9999;
	dest.x = 9999;
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;

	dest.w = 32;
	dest.h = 32;
	hit = false;
	timerEnd = 0;
	randomInv = 0;

	bullet = TextureManager::LoadTexture("assets/bullet.png");
}