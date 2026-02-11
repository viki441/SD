#pragma once

#include <SDL.h>
#include <SDL_image.h>


#include "TextManager.h"
#include <iostream>
#include "Digger.h"
#include "Enemy.h"

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
//-----------------------------------------STAGE RELATED
	bool isRunning;
	SDL_Window* window;
	TextManager* font;
	
//----------------------------------------PLAYER RELATED
	vector<Enemy*> enemies;
	Digger* digger = nullptr;
	

//----------------------------------------MAP RELATED
	Map map;
	SDL_Texture* background;
	
	int level;

	



private:
	void levelUp(int level); //will destroy and create a new map;
	void updateMap(); // just give new level
};

