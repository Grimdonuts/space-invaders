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
		
		int timerEnd = 0;
		int invadermody = 0;
		int invadermodx = 1;
	private:
		SDL_Texture* invader;
		SDL_Rect src;
		SDL_Rect dest;
};