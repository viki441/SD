#pragma once
//#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"


enum class Direction
{
	NONE, UP, DOWN, LEFT, RIGHT
};


class GameObject
{
public:

	//GameObject(const char* textureSheet, int x, int y);
	virtual ~GameObject() = default;

	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void changeAnimation(Direction direction) = 0;
	virtual void dig(Map& map) = 0;



protected:
	int xpos;
	int ypos;

	//must be here because nobbin is also digging
	int tileX; // for adding dug on top
	int tileY;

	int height = 64;
	int width = 64;
	int frame = 0;
	Direction direction = Direction::NONE;

	SDL_Texture* objTexture;

	//SDL_Rect srcRect, destRect;


	SDL_Rect getRect() const
	{
		return {xpos, ypos, width, height};
	}

};