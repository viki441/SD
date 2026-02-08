#include "Game.h"
#include "TextureManager.h"
#include <stdexcept>
#include <iostream>

using namespace std;

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


    //proverka
    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) { cout << SDL_GetError();}

   
    //alternative: diggerTex = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\VRDIG1.bmp"); 
    /*SDL_Texture* bg = TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\maps\\level1.png");  
     SDL_Rect background;
     background.x = 0;
     background.y = 0;*/



    
    //SEPARATE MAYBE
    digger = new Digger(00, 10, TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\DiggerbulletRight.png"));
    Enemy* nobbin = new Enemy(100,100, TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\nobbin\\VNOB1.bmp"));

    enemies.push_back(nobbin);

    background = TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\flower.png");
    if (!background) std::cout << "Failed to load background: " << IMG_GetError() << std::endl;
    
}
void Game::handleEvents() //update graph only on digger's movement 
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


    //avoid diagonal movement
    //DIGGER MOVEMENT
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    digger->updateDirection(keystate);
    


}
void Game::update()
{
    for(GameObject* enemy : enemies)
        enemy->update();

        digger->update();
        digger->dig(map);
        //digger->setDug(digger->getNextX(), digger->getNextY(), map);
         
    //nobbin->update();
    
    
}
void Game::render()
{
    SDL_RenderClear(renderer);
    //add stuff to renderer
    SDL_RenderCopy(renderer, background, NULL, NULL);
    
    try
    {
        map.drawMap();
    }
    catch(...)
    {
        cerr << "wtf";
    }

    for (GameObject* enemy : enemies)
        enemy->render(renderer);

    digger->render(renderer);
    SDL_RenderPresent(renderer);
    
   

}
void Game::clean()
{
    for (GameObject* enemy : enemies)
        delete enemy;
    delete digger;
    enemies.clear();

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    cout << "Game cleaned\n" << endl;
}