#pragma once
#include "Game.h"

class Barrier {
public:
	Barrier();
	~Barrier();
	void LoadBarrier(int x, int y);

	SDL_Texture* GetBarrierTexture() { return barrier; }
	SDL_Rect GetBarrierSrcRect() { return src; }
	SDL_Rect GetBarrierDestRect() { return dest; }
	bool shot = false;
private:
	SDL_Texture* barrier;
	SDL_Rect src;
	SDL_Rect dest;
};