#include "Game.h"
#include "TextureManager.h"
#include <stdexcept>
#include "GameObject.h"
using namespace std;


GameObject* player;
GameObject* nobbin;


SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
 
}

Game::~Game()
{

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    

    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;


    //initialization           
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Init successful\n";


        //window creation
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
        
            cout << "Window is created successfuly\n";
        }
        else throw runtime_error(SDL_GetError());

        //renderer creation
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 100, 100, 25, 0);
            cout << "Renderer is created successfuly\n";
        }
        else throw runtime_error(SDL_GetError());
        isRunning = true;
        map.init();

    }
    else
    {
        isRunning = false;
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }



    //PLAYER
    //proverka
    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) { cout << SDL_GetError();}

   
    //alternative: playerTex = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\VRDIG1.bmp"); 
 
    
    
    /*   SDL_Texture* bg = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\maps\\level1.png");  
     SDL_Rect background;
     background.x = 0;
     background.y = 0;*/
    //bg = new GameObject("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\level1.bmp", 110, 50);
    //da e golqmo?

    player = new GameObject("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\Diggerbullet.png", 0, 10);
    nobbin = new GameObject("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\nobbin\\VNOB1.bmp", 111, 111);


    background = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\flower.png");
    if (!background) std::cout << "Failed to load background: " << IMG_GetError() << std::endl;
    
    



}
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        //throw runtime_error(SDL_GetError());
        break;
    }
}
void Game::update()
{
   
    nobbin->update();
    player->update();
    
}
void Game::render()
{
    SDL_RenderClear(renderer);
    //add stuff to renderer
    SDL_RenderCopy(renderer, background, NULL, NULL);
    
    map.drawMap();
    nobbin->render();
    player->render();

    SDL_RenderPresent(renderer);
    
   

}
void Game::clean()
{
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    cout << "Game cleaned\n" << endl;
}