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


        //------------------------------------------------------------------------------window creation
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {

            cout << "Window is created successfuly\n";
        }
        else throw runtime_error(SDL_GetError());

        //------------------------------------------------------------------------RENDERER, LADIES AND GENTLEMEN
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            cout << "Renderer is created successfuly\n";
        }
        else throw runtime_error(SDL_GetError());
        isRunning = true;

        //-----------------------------------------------------------------MAP
        map.init();
       

    }
    else
    {
        isRunning = false;
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }


    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) { cout << SDL_GetError();}

    
//--------------------------------------------------------------MOVIN' STUFF------------------------------------------------------------------
    digger = new Digger(0, 60, TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\DiggerbulletRight.png"));
    Enemy* nobbin = new Enemy(896,60, TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\nobbin\\Nobbin.png"));
    enemies.push_back(nobbin);


//---------------------------------------------------BACKGROUND-----------------------------------------------------
    background = TextureManager::loadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\Tile.png");
    if (!background) std::cout << "Failed to load background: " << IMG_GetError() << std::endl;
    


//-----------------------------------------------------------------TEXT STUFF
    font = new TextManager(renderer);
    for (char c = '0'; c <= '9'; c++)
    {
        string path = "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\\\text\\";
        path = path + "VNUM" + c + ".bmp";
        font->loadChar(c, path);
    }

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
        digger->update();
        digger->dig(map);

        for (Enemy* enemy : enemies)
        {
            enemy->chase(map, digger->getTileX(), digger->getTileY());           
            enemy->update();
        }
            
}
void Game::render()
{
    SDL_RenderClear(renderer);

    SDL_Rect srcB = {0,0, MAP_WIDTH, MAP_HEIGHT + MAP_OFFSET_Y};
    SDL_Rect destB = { 0, MAP_OFFSET_Y, MAP_WIDTH, MAP_HEIGHT + MAP_OFFSET_Y };
    SDL_RenderCopy(renderer, background, &srcB, &destB);
  
    map.drawMap();


    digger->render(renderer);
 

    for (GameObject* enemy : enemies)
    {
        enemy->render(renderer);
    }
        

   
    font->renderNumbers( 10, 10, digger->getPoints());
    SDL_RenderPresent(renderer);
    
   
    //cout << digger->getPoints() << endl;


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