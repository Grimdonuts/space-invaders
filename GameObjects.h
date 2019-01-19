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
		GameObjects();
		GameObjects(int inFrames, int inSpeed);
		~GameObjects();

		void LoadInvaders(int arr[22][29]);
		void DrawInvaders();
		void MoveInvaders();
		void Update(input_cmd cmd);
		void LoadPlayer();

	private:
		bool movingRight = true;
		bool animated = false;
		int frames = 0;
		int speed = 100;

		int playerx = 605;
		int playery = 625;
		int invadersx = 0;
		int invadersy = 0;
		int movements = 0;

		SDL_Rect src, dest;
		SDL_Rect invSrc, invDest;
		
		SDL_Texture* player;
		SDL_Texture* ground;
		SDL_Texture* invaders1;
		SDL_Texture* invaders2;
		

		int map[22][29];
};