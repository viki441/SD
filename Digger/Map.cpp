#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <string>

void Map::init()
{

	//to add -> cherry, gold bags
	gold = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\Gold.png"); // 3
	dug = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\dug.bmp"); // 1 
	emerawd = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\Emerald.png");// 2

	if (!dug) std::cout << "DUG FAILED\n";
	if (!emerawd) std::cout << "EMERALD FAILED\n";
	if (!gold) std::cout << "GOLD FAILED\n";

}


Map::Map()
	:lvl(1)
{

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			objects[i][j] = 0;
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
			objects[i][j] = 0;
		}
	}
	//to add -> cherry, gold bags
	gold = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\VBONUS.bmp"); // 3
	dug = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\dug.png"); // 1 
	emerawd = TextureManager::loadTexture("C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\BMPS\\map\\VEMERAWD.bmp");// 2

	//dug is going to be 30x32 where h and w are dictated by  digger pos
	//layer under is going to be the default dirt -> when digger comes, he leaves 'dug' to mimic making a path while still visually showing a thin line, where the graph is NOT connected

	//TO DO: load background
	loadMap();

	src.x = src.y = 0;
	src.w = dest.w = 64;
	src.h = dest.h = 64;


	dest.x = dest.y = 0;
}




void Map::loadObjects(const char* filename) //its in h too, cuz it works with tiles
{

	ifstream level(filename);

	if (!level) throw std::runtime_error("Problem opening file\n");
	
	//building map
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (!(level >> objects[row][col]))
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
	loadObjects(evaluateLevel(lvl));

	//dmap.addEdge()


}
const char* Map::evaluateLevel(int n)
{
	switch (n)
	{
	case 1:
		return "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\levels\\level1.txt"; break;

	default:
		return "";
	}

}






void Map::drawMap()
{
	cout << "Tried to draw" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int type = objects[i][j];
			
			dest.x = j * 64;
			dest.y = i * 64;
			
			evaluateTile(type);
		}
	}
}


void Map::evaluateTile(const int type)
{
	switch (type)
	{
	case 0: break;


	case 1: TextureManager::draw(dug, src, dest); break;

	case 2: TextureManager::draw(emerawd, src, dest); break;
		//the others are conditional
	case 3: TextureManager::draw(gold, src, dest); break; // this is the fallen gold remains

		//to add -> cherry, gold bags
	}
}






Map::~Map()
{

}






