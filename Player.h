#pragma once
#include <cstdint>
#include "Game.h"

class Player {
	public:
		int playerx;
		int playery;

		void LoadPlayer();
		void UpdatePlayerCoord();
		
		SDL_Texture* GetPlayerTexture(){ return player; };
		SDL_Rect GetPlayerSrcRect() { return src; }
		SDL_Rect GetPlayerDestRect() { return dest; }
	private:
		SDL_Texture* player;
		SDL_Rect src;
		SDL_Rect dest;
		
};