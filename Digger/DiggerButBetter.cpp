#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <cstdint>; 

#include "Restraints.h"
#include "Game.h"
using namespace std;


Game* game = nullptr;

int main(int argc, char* argv[])
{
    try {
        const int FPS = 60; // closest to refresh rate of monitors
        const int DELAY = 1000 / FPS;


        Uint32 frameStart;
        int frameTime;




        game = new Game();
        //960 x 640
        game->init("digger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAP_WIDTH, MAP_HEIGHT + MAP_OFFSET_Y, false);

        while (game->running())
        {
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (DELAY > frameTime)
                SDL_Delay(DELAY - frameTime);
        
        }


        game->clean();


        return 0;

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
    }


 


}
