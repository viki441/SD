#include "TextManager.h"
#include "TextureManager.h"


TextManager::TextManager(SDL_Renderer* renderer)
	:renderer(renderer), width(32), height(32)
{}


TextManager::~TextManager()
{
	for (auto& pair : text)
		SDL_DestroyTexture(pair.second);
}


void TextManager::loadChar(char c, const string& path)
{
	text[c] = TextureManager::loadTexture(renderer, path.c_str());
}



void TextManager::renderNumbers(int x, int y, int points)
{
	
	std::string txt = "00000";

	int i = 4;
	while (points > 0 && i >= 0)
	{
		txt[i] = '0' + (points % 10);
		points /= 10;
		i--;
	}

	renderText(x, y, txt);
}


void TextManager::renderText(int x, int y, const string& txt)
{
	SDL_Rect dest{ x, y, width, height };
	for (char c : txt)
	{
		if (text.count(c))
			SDL_RenderCopy(renderer, text[c], nullptr, &dest);
		
		dest.x += width;
	}
}
