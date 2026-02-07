#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <cstdint>; 

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
        game->init("digger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);

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
    //textures
    //see digger class, maybe add a setter here?
 /*   SDL_Texture* diggerTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\digger\\VRDIG1.bmp");
    SDL_Texture* hobbinTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\hobbin\\VRHOB1.bmp");
    SDL_Texture* nobbinTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\nobbin\\VNOB1.bmp");
*/


 


}



//// Create a window
//SDL_Window* window = SDL_CreateWindow(
//    "SDL2 Test Window",
//    SDL_WINDOWPOS_CENTERED,
//    SDL_WINDOWPOS_CENTERED,
//    800, 600,
//    SDL_WINDOW_SHOWN
//);

//if (!window) {
//    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//    SDL_Quit();
//    return 1;
//}

//// Create a renderer
//SDL_Renderer* renderer = SDL_CreateRenderer(
//    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
//);



//SDL_Texture* heroTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\pumpkin.png");
//if (!heroTexture) cerr << "Failed to load hero\n" << endl;

////where to put hero
//SDL_Rect heroRect;
//heroRect.x = 100;
//heroRect.y = 200;
//heroRect.w = 32;
//heroRect.h = 32;


//// Main loop
//bool running = true;
//SDL_Event event;


//while (running) 
//{
//    //MOVING!
//    while (SDL_PollEvent(&event)) 
//    {
//        if (event.type == SDL_QUIT) running = false;
//        if (event.type == SDL_KEYDOWN)
//        {
//            switch (event.key.keysym.sym)
//            {
//            case SDLK_LEFT: heroRect.x -= 5; break;
//            case SDLK_RIGHT: heroRect.x += 5; break;
//            case SDLK_UP: heroRect.y -= 5; break;
//            case SDLK_DOWN: heroRect.y += 5; break;
//            }
//        }
//    }

//    // Clear screen to dark gray
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);

//    SDL_RenderCopy(renderer, heroTexture, NULL, &heroRect);

//    // Present the renderer
//    SDL_RenderPresent(renderer);
//}

// Cleanup
/*SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);*/


