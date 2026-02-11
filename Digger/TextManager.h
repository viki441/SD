#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

using namespace std;
class TextManager
{
public:
	
	TextManager(SDL_Renderer* renderer);
	~TextManager();

	
	void loadChar(char c, const string& path);


	void setPoints(int points); // will get points from digger on each point's changes
	void update();
	void renderNumbers(int x, int y, int points); // the string for looping
	void renderText(int x, int y, const string& text);

private:
	
	unordered_map<char, SDL_Texture*> text;
	SDL_Renderer* renderer;

	int width;
	int height;

};