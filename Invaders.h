#pragma once
#include "Game.h"

class Invaders {
	public:
		Invaders();
		~Invaders();
		void LoadInvaders(int invaderType);
		void SetInvadersXY(int x, int y);
		void AnimateInvaders(int speed);

		SDL_Texture* GetInvaderTexture() { return invader; };
		SDL_Rect GetInvaderSrcRect() { return src; }
		SDL_Rect GetInvaderDestRect() { return dest; }
		bool dead = false;
		bool deathplayed = false;
		Timer deathTimer;
		int timerEnd = 0;
	private:
		SDL_Texture* invader;
		SDL_Rect src;
		SDL_Rect dest;
};