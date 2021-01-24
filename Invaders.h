#pragma once
#include "Game.h"

class Invaders {
	public:
		Invaders();
		~Invaders();
		void LoadInvaders();
		void SetInvadersXY(int x, int y);
		void AnimateInvaders(int speed);

		SDL_Rect GetInvaderSrcRect() { return src; }
		SDL_Rect GetInvaderDestRect() { return dest; }
		bool dead = false;
		
		int timerEnd = 0;
		int invadermody = 0;
		int invadermodx = 1;
		SDL_Texture* invader;
		SDL_Texture* deadInvader;
	private:
		SDL_Rect src;
		SDL_Rect dest;
};