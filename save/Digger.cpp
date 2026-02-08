#include "Digger.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;


Digger::Digger(int x, int y, SDL_Texture* tex)
{
    this->xpos = x;
    this->ypos = y;
    this->objTexture = tex;
}


void Digger::update() //TO DO: ADD VERTICES IF NEEDED
{
    //cout << "update" << endl;
    frame = (SDL_GetTicks() / 4) % frameCount;

    int dx = 0;
    int dy = 0;

    switch (direction) 
    {
    case Direction::UP:    dy = -1; break;
    case Direction::DOWN:  dy = 1; break;
    case Direction::LEFT:  dx = -1; break;
    case Direction::RIGHT: dx = 1; break;
    default: return;
    }


    int nextX = xpos + dx * 4;
    int nextY = ypos + dy * 4;


    //digger can go anywhere as long as it's on the screen
    if (nextX >= 0 && nextX <= 960 && nextY >= 0 && nextY <= 640)
    {
        xpos = nextX;
        ypos = nextY;
        changeAnimation(direction);
    }

}

void Digger::updateDirection(const Uint8* keystate)
{
    if (keystate[SDL_SCANCODE_UP])
        direction = Direction::UP;

    else if (keystate[SDL_SCANCODE_DOWN])
        direction = Direction::DOWN;

    else if (keystate[SDL_SCANCODE_LEFT])
        direction = Direction::LEFT;

    else if (keystate[SDL_SCANCODE_RIGHT])
        direction = Direction::RIGHT;

    else
        direction = Direction::NONE;
}

void Digger::changeAnimation(Direction direction)
{
    if (direction == Direction::DOWN)
        objTexture = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\DiggerbulletDown.png");
    
    else if (direction == Direction::LEFT)
        objTexture = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\DiggerbulletLeft.png");

    else if(direction == Direction::UP)
        objTexture = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\DiggerbulletUp.png");
    else
        objTexture = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\digger\\DiggerbulletRight.png");
}

void Digger::dig(Map& map)
{
    int diggerDirection = 0;
    if (direction == Direction::DOWN || direction == Direction::UP) // vertical is positive
        diggerDirection = 1;
    else if (direction == Direction::RIGHT || direction == Direction::LEFT)
        diggerDirection = -1;

    map.digTile(xpos + 32, ypos + 32, diggerDirection);
    //cout << "dig: " << xpos << " " << ypos << endl;
}





const Direction Digger::getDirection() const
{
    return direction;
}


const int Digger::getNextX() const
{
    return xpos;
}
const int Digger::getNextY() const
{
    return ypos;
}


void Digger::render(SDL_Renderer* renderer)
{
    SDL_Rect src = { frame * width, 0 , width, height };
    SDL_Rect dest = { xpos, ypos, width, height };

    SDL_RenderCopy(renderer, objTexture, &src, &dest);

}