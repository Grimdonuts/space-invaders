#pragma once
#include "Game.hpp"

class Barrier {
public:
	Barrier();
	~Barrier();
	void LoadBarrier(int x, int y);

	SDL_Rect GetBarrierSrcRect() { return src; }
	SDL_Rect GetBarrierDestRect() { return dest; }
	bool shot = false;
	SDL_Texture* barrier;
private:
	SDL_Rect src;
	SDL_Rect dest;
};