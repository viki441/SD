#pragma once

#include <SDL.h>
#include <SDL_image.h>
//SEPARATE FOR BULLET
enum class Type
{
	//note: dropping gold will be a function, and broken gold will be a changed sprite

	EMERAWD = 2, GOLD, CHERRY
};
class Objects
{

private:
	Type type;
	int value; // the points youll get
	SDL_Texture* tex;
	int xPos;
	int yPos;

private:
	void update();
	void render();

};