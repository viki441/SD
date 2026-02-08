#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <string>

void Map::init()
{

	//to add -> cherry, gold bags
	dugH = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\DugH.png"); // 3
	dugV = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\DugV.png"); // 1 
	finalDug = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\level1.bmp"); // 4 
	emerawd = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\Emerald.png");// 2

	if (!dugH) std::cout << "DUG FAILED\n";
	if (!emerawd) std::cout << "EMERALD FAILED\n";
	if (!dugV) std::cout << "GOLD FAILED\n";

}


Map::Map()
	:lvl(1)
{

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			tiles[i][j] = 0;
		}
	}

	//dug is going to be 30x32 where h and w are dictated by  digger pos
	//layer under is going to be the default dirt -> when digger comes, he leaves 'dug' to mimic making a path while still visually showing a thin line, where the graph is NOT connected

	//TO DO: load background
	loadMap();

	src.x = src.y = 0;
	src.w = dest.w = 64;
	src.h = dest.h = 64;


	dest.x = dest.y = 0;
}
Map::Map(int level)
	:lvl(level)
{

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			tiles[i][j] = 0;
		}
	}
	////to add -> cherry, gold bags
	//gold = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\VBONUS.bmp"); // 3
	//dug = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\dug.png"); // 1 
	//emerawd = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\VEMERAWD.bmp");// 2

	//dug is going to be 30x32 where h and w are dictated by  digger pos
	//layer under is going to be the default dirt -> when digger comes, he leaves 'dug' to mimic making a path while still visually showing a thin line, where the graph is NOT connected

	//TO DO: load background
	loadMap();

	src.x = src.y = 0;
	src.w = dest.w = 64;
	src.h = dest.h = 64;


	dest.x = dest.y = 0;
}


void Map::updateGraph(int xpos, int ypos)
{
	int currRow = xpos % 64;
	int currCol = ypos % 64;
	
}

void Map::loadTiles(const char* filename) //its in h too, cuz it works with tiles
{

	ifstream level(filename);

	if (!level) throw std::runtime_error("Problem opening file\n");
	
	//building map
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (!(level >> tiles[row][col]))
			{
				throw std::runtime_error("Invalid map file format");
			}
		}
	}

	level.close();
}

void Map::loadMap()
{
	//choose level
	loadTiles(evaluateLevel(lvl));

	//initially build map on tiles
	int type = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			type = tiles[row][col];
			if (type == 1)//dug			
				map.setWalkable(row, col, true);
			
			else
				map.setWalkable(row, col, false);
		}
	}

}

const char* Map::evaluateLevel(int n)
{
	switch (n)
	{
	case 1:
		return "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\levels\\level.txt"; break;

	default:
		return "";
	}

}






void Map::drawMap()
{
	//cout << "Tried to draw" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int type = tiles[i][j];
			
			dest.x = j * 64;
			dest.y = i * 64;
			
			evaluateTile(type);
		}
	}
}

void Map::digTile(int x, int y, int direction)
{//vertical is positive!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int tilePosX = x / 64;
	int tilePosY = y / 64;
	

	if (tiles[tilePosY][tilePosX] != 4) // can be emerald
	{
		cout << "DIRECTION: " << direction << endl;

		try
		{

			//horizontal movement and 
			if (direction == -1 && tiles[tilePosY][tilePosX] == 1)
			{
				tiles[tilePosY][tilePosX] = 4;
				map.setWalkable(tilePosX, tilePosY, 4);
				cout << "Horizontal movement" << direction << endl;
				return;
			}
			//vertival movement and horizontal tile
			if (direction == 1 && tiles[tilePosY][tilePosX] == 3)
			{
				tiles[tilePosY][tilePosX] = 4;
				map.setWalkable(tilePosX, tilePosY, 4);
				cout << "Vertical movement:" << direction << endl;
				return;
			}

			if (tiles[tilePosY][tilePosX] == 4) return;
	
			if (direction == 1)//vertical
			{
				tiles[tilePosY][tilePosX] = 1; //adding vertical
				map.setWalkable(tilePosX, tilePosY, 1);
			}

			if (direction == -1)
			{
				tiles[tilePosY][tilePosX] = 3; //adding vertical
				map.setWalkable(tilePosX, tilePosY, 3);
			}
			
			
			//if (direction <0)			
			//	dug = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\DugH.png"); // 1 
			//
			//else if(direction > 0)
			//	dug = TextureManager::loadTexture(Game::renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\DugV.png"); // 1 
			//

			
			
		}
		catch (const std::exception& e)
		{
			cerr << e.what();
		}

	}	
}

void Map::evaluateTile(const int type)
{
	switch (type)
	{
	case 0: break;


	case 1: TextureManager::draw(Game::renderer, dugV, src, dest); break;

	case 2: TextureManager::draw(Game::renderer, emerawd, src, dest); break;
		//the others are conditional
	case 3: TextureManager::draw(Game::renderer, dugH, src, dest); break; // this is the fallen gold remains

	case 4: TextureManager::draw(Game::renderer, finalDug, src, dest); break;
		//to add -> cherry, gold bags
	}
}






Map::~Map()
{

}






