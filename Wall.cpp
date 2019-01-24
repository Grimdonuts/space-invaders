#include "Wall.h"
#include "TextureManager.h"

Wall::Wall(){}
Wall::~Wall(){}
void Wall::LoadWall(int x, int y)
{
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	
	dest.w = src.w * 2;
	dest.h = src.h * 2;

	if (dest.x < 500)// left wall
	{
		dest.x = x - (dest.w / 2);
	}
	else // right wall
	{
		dest.x = x + (dest.w / 2);
	}
	dest.y = y;

	for (int i = 0; i < 22; i++)
	{
		wallYCoords.push_back(i * 64);
	}
	wall = TextureManager::LoadTexture("assets/wall.png");
}

void Wall::SetWallY(int y)
{
	dest.y = y;
}
