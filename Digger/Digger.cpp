#include "Digger.h"

Digger::Digger(Coordinates c, SDL_Texture* t)
	:Entity(c, t), points(0), gunCooldown(0.0), lives(3)
{}

Digger::~Digger()
{
}


void Digger::update(double deltaTime)
{

}