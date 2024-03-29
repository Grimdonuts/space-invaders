#pragma once
#include "Game.hpp"

class Wall {
	public:
		Wall();
		~Wall();
		void LoadWall(int x, int y, float wallYLength);
		void SetWallY(int y);

		SDL_Rect GetWallSrcRect() { return src; }
		SDL_Rect GetWallDestRect() { return dest; }
		int GetYCoord(int index) { return wallYCoords[index]; }
		SDL_Texture* wall;
	private:
		int wallYCoords[100] = {};
		SDL_Rect src;
		SDL_Rect dest;
		
};