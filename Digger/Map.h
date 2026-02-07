#pragma once

#include "Graph.h"

#include <SDL.h>
#include <SDL_image.h>

/*the map consists of:
* 
* 
src - for itself
map - graph for logic of movement
int* - for cosmetic show

*/

class Map
{
public:
	Map();
	Map(int level);
	~Map();

	
	void init();

	//for graph
	void loadMap();

	//level number is going to be decided by a switch somewhere else, and the right filename is guaranteed here
	void loadObjects(const char* fileName); 
	const char* evaluateLevel(int n);



	void evaluateTile(const int type);
	void drawMap();
	


private:
	static const int ROWS = 10;
	static const int COLS = 15;

	SDL_Rect src, dest;

	//to add -> cherry, gold bags
	SDL_Texture* gold;
	SDL_Texture* dug;
	SDL_Texture* emerawd;

	
	Graph map; // logical assumption where u can go
	int lvl;// GAME will give the map a lvl to build on
	int objects[ROWS][COLS]; // this is staying an array, but is only serves cosmetical features anyway




};