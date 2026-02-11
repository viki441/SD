#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* fileName);
	static void draw(SDL_Renderer* renderer, SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dest);
};