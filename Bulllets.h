#pragma once
#include "Game.h"

class Bullets {
	public:
		Bullets();
		~Bullets();
		bool hit = false;

		void LoadBullets();
		void SetBulletXY(int x, int y);
		SDL_Texture* GetBulletTexture() { return bullet; };
		SDL_Rect GetBulletSrcRect() { return src; }
		SDL_Rect GetBulletDestRect() { return dest; }
	private:
		SDL_Texture* bullet;
		SDL_Rect src;
		SDL_Rect dest;
};