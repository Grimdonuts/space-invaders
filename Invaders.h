#pragma once
#include "Game.h"

class Invaders {
	public:
		Invaders();
		~Invaders();
		void LoadInvaders(int invaderType);
		void SetInvadersXY(int x, int y);
		void AnimateInvaders();

		SDL_Texture* GetInvaderTexture() { return invader; };
		SDL_Rect GetInvaderSrcRect() { return src; }
		SDL_Rect GetInvaderDestRect() { return dest; }
		int GetYCoord(int index) { return dest.x; }
		int GetXCoord(int index) { return dest.x; }
		
	private:
		int invadersCount = 50;
		int invaderSpeed = 0;
		SDL_Texture* invader;
		SDL_Rect src;
		SDL_Rect dest;
};