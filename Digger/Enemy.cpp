#include "Enemy.h"

Enemy::Enemy(Coordinates c, SDL_Texture* t)
	:Entity(c, t), velocity(1.0) 
{
}

Enemy::~Enemy()
{
}