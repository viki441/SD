#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(SDL_Renderer* renderer, const char* texture)
{
	SDL_Surface* tmpSurface = IMG_Load(texture);
	if (!tmpSurface)
	{
		cerr << "TextureManager: Image failed loading: " << IMG_GetError() << endl;
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	if (!tex)
	{
		cerr << "TextureManager: Texture failed creating: " << SDL_GetError() << endl;
	}

	return tex;
}



void TextureManager::draw(SDL_Renderer* renderer, SDL_Texture* tex, const  SDL_Rect& src, const  SDL_Rect& dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);

}