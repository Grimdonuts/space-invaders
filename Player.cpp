#include "Player.h"
#include "TextureManager.h"

void Player::LoadPlayer()
{
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.x = 0;
	dest.y = 0;
	dest.w = src.w * 2;
	dest.h = src.h * 2;

	playerx = playerx - (dest.w / 2);
	player = TextureManager::LoadTexture("assets/tank.png");
}

void Player::UpdatePlayerCoord()
{
	src.h = 32;
	src.w = 32;
	src.x = 0;
	src.y = 0;

	dest.x = playerx;
	dest.y = playery;
	dest.w = src.w * 2;
	dest.h = src.h * 2;
}