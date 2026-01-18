#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) 
{
    // Initialize SDL2 --- belongs in main
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
        Game game;
        game.run();

    

    SDL_Quit();
    return 0;

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
 

