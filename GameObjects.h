#pragma once
#include "Game.h"

struct input_cmd{
    uint32_t up:1;
    uint32_t down:1;
    uint32_t right:1;
    uint32_t left:1;
    uint32_t fire:1;
    uint32_t bomb:1;
};

class GameObjects {
	public:
		GameObjects(int inFrames, int inSpeed);
		~GameObjects();

		void LoadInvaders(int arr[22][29]);
		void DrawInvaders();
		void MoveInvaders();
		void Update(input_cmd cmd);
		void DrawBullets(input_cmd cmd);

	private:
		int resolutionW;
		int resolutionH;
		bool movingRight = true;
		bool animated = false;
		bool movementChanged = false;
		int frames = 0;
		int speed = 100;

		int playerx = 0;
		int playery = 0;
		int invadersx = 0;
		int invadersy = 0;

		SDL_Rect src, dest;
		SDL_Rect invSrc, invDest;
		SDL_Rect firstinvSrc, firstinvDest;
		SDL_Rect wallSrc, wallDest;
		SDL_Rect wall2Src, wall2Dest;
		SDL_Rect bullSrc, bullDest;
		
		SDL_Texture* wall;
		SDL_Texture* player;
		SDL_Texture* bullet;
		SDL_Texture* invaders1;
		SDL_Texture* invaders2;
		

		int map[22][29];
};