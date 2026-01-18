#include "Entity.h"

Entity::Entity(Coordinates c, SDL_Texture* t)
	:coordinates(c), texture(t)
{
}

void Entity::render(SDL_Renderer* renderer)
{
	SDL_Rect dst{ coordinates.x, coordinates.y, 32, 32 };
	SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Entity::update(double deltaTime)
{

}