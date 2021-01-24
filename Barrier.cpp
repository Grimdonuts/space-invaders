#include "Barrier.h"
#include "TextureManager.h"

Barrier::Barrier() {}
Barrier::~Barrier() {}

void Barrier::LoadBarrier(int x, int y)
{
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;

	dest.w = src.w;
	dest.h = src.h;

	dest.x = x;
	dest.y = y;
}