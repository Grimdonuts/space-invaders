#pragma once
#include "Game.h"

class Bullets {
	public:
		Bullets();
		~Bullets();
		bool hit = false;
		int timerEnd = 0;
		int randomInv = 0;

		void Clear();
		void LoadBullets();
		void SetBulletXY(int x, int y);
		SDL_Rect GetBulletSrcRect() { return src; }
		SDL_Rect GetBulletDestRect() { return dest; }
		SDL_Texture* bullet;
	private:
		SDL_Rect src;
		SDL_Rect dest;
};