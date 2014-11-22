#include <SDL.h>
#include <iostream>
#include "LTimer.h"
#include <time.h>

#include "Game.h"
/*
FILE:main.cpp
AUTHOR:NAHIDUL SEKANDER
DATE:09/16/2014
*/

//define how many frames per second for the program to run
const int FRAMES_PER_SECOND = 60;
//amount of time we need to delay the game between loops to keep our constant frame rate
const int DELAY_TIME = 1000.0f /FRAMES_PER_SECOND;

int main(int argc, char** argv)
{
    //The frames per second timer
    LTimer fpsTimer;

    //The frames per second cap timer
    LTimer capTimer;

    //Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();

	printf("GAME INITIALIZE ATTEMPT...\n");
	if(Game::Instance() ->init())
	{

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		printf("GAME INITIALIZE SUCCESS...\n");
		while(Game::Instance() ->running())
		{
            //Start cap timer
            capTimer.start();

            //Calculate and correct fps
            float avgFPS = countedFrames / (fpsTimer.getTicks()/1000.0f);
            if(avgFPS > 2000000)
                avgFPS = 0;

            //printf("AVERAGE FRAMES PER SECOND(CAP): %d\n", avgFPS)

			Game::Instance() ->handleEvents();
			Game::Instance() ->update();
			Game::Instance() ->render();

            //swap the front/back buffer to update the screen
			SDL_GL_SwapWindow(Game::Instance() ->getWindow());
			++countedFrames;

			//If frame finished early
			int frameTicks = capTimer.getTicks();
			if(frameTicks < DELAY_TIME)
			//wAIT REMAINNG TIME
                SDL_Delay(DELAY_TIME - frameTicks);
		}

		Game::Instance() ->clean();
	}

	return 0;
}
