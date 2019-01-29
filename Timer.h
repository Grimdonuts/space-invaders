#pragma once
#include <cstdint>
#include "Game.h"

class Timer
{
    public:
		Timer();

		void start();
		void stop();
		void pause();
		void unpause();

		uint32_t getTicks();

		bool isStarted();
		bool isPaused();

    private:
		uint32_t startTicks;

		uint32_t pausedTicks;

		bool paused;
		bool started;
};