#pragma once
#include "Game.h"

class Wall {
	public:
		Wall();
		~Wall();
		void LoadWall(int x, int y, float wallYLength);
		void SetWallY(int y);

		SDL_Texture* GetWallTexture(){ return wall; }
		SDL_Rect GetWallSrcRect() { return src; }
		SDL_Rect GetWallDestRect() { return dest; }
		int GetYCoord(int index) { return wallYCoords[index]; }
	private:
		std::vector<int> wallYCoords;
		SDL_Texture* wall;
		SDL_Rect src;
		SDL_Rect dest;
		
};