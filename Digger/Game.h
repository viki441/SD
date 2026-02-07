#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Map.h"
using namespace std;


class Game 
{
public:
	static SDL_Renderer* renderer;

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }



private:
	bool isRunning;
	SDL_Window* window;
	int cnt = 0;
	int level;
	int enemies[6]; //on screen max 5 --> 0 & 1 for stat
	Map map;
	SDL_Texture* background;


private:
	void levelUp(int level); //will destroy and create a new map;
	void updateMap(); // just give new level
};

