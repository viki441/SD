#include "Enemy.h"

Enemy::Enemy(int x, int y, SDL_Texture* tex)
{
    this->xpos = x;
    this->ypos = y;
    this->objTexture = tex;
}


void Enemy::update()
{
}


void Enemy::dig(Map& map)
{
}

void Enemy::changeAnimation(Direction direction)
{

}
void Enemy::render(SDL_Renderer* renderer)
{
    SDL_Rect dest = { xpos, ypos, width, height };
    SDL_RenderCopy(renderer, objTexture, nullptr, &dest);

}