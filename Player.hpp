#pragma once
#include <cstdint>
#include "Game.hpp"

class Player {
	public:
		int playerx;
		int playery;

		int playerLives = 3;
		int timerEnd = 0;
		bool hit = false;
		Player();
		~Player();
		void LoadPlayer();
		void UpdatePlayerCoord();
		void SetPlayerLivesCoord(int x, int y, int destw, int desth);

		SDL_Rect GetPlayerSrcRect() { return src; }
		SDL_Rect GetPlayerDestRect() { return dest; }
		SDL_Texture* player;
		SDL_Texture* deadTexture;
	private:
		SDL_Rect src;
		SDL_Rect dest;
		
};