#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <cstdlib>
#include <string>

//ENEMMMMMMMMMMMMMMMMMMMTTYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY

struct Node
{
	int x, y;
	int g, h;
	Node* parent;

	int f() const { return g + h; }
};

int heuristic(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

static Node* findNode(std::vector<Node*>& list, int x, int y)
{
	for (Node* n : list)
		if (n->x == x && n->y == y)
			return n;
	return nullptr;
}
static Node* getLowestF(std::vector<Node*>& openList)
{
	Node* best = openList[0];
	for (Node* n : openList)
		if (n->f() < best->f())
			best = n;
	return best;
}

bool Map::isWalkable(int x, int y)
{
	if (x < 0 || y < 0 || x >= COLS || y >= ROWS)
		return false;

	return map.isWalkable(x, y);
	
}


//enemy - strat
vector<SDL_Point> Map::findPath(SDL_Point start, SDL_Point goal)
{
	/*if (!isWalkable(goal.x, goal.y))
	{
		std::cout << "GOAL NOT WALKABLE: "
			<< goal.x << "," << goal.y << std::endl;
	}*/

	std::vector<SDL_Point> path;
	// Sanity checks
	/*if (!isWalkable(start.x, start.y))
		return path;*/

	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	// Create start node
	Node* startNode = new Node{
		start.x,
		start.y,
		0,
		heuristic(start.x, start.y, goal.x, goal.y),
		nullptr
	};

	openList.push_back(startNode);

	// A* loop
	while (!openList.empty())
	{
		Node* current = getLowestF(openList);

		
		if (current->x == goal.x && current->y == goal.y)
		{
			Node* n = current;
			while (n)
			{
				path.push_back({ n->x, n->y });
				n = n->parent;
			}
			std::reverse(path.begin(), path.end());
			break;
		}

		// Move current from open to closed
		openList.erase(
			std::remove(openList.begin(), openList.end(), current),
			openList.end()
		);
		closedList.push_back(current);

		// 4-directional neighbors
		const int dx[4] = { 1, -1, 0, 0 };
		const int dy[4] = { 0, 0, 1, -1 };

		for (int i = 0; i < 4; i++)
		{
			int nx = current->x + dx[i];
			int ny = current->y + dy[i];

			if (!isWalkable(nx, ny))
				continue;

			if (findNode(closedList, nx, ny))
				continue;

			int newG = current->g + 1;
			Node* neighbor = findNode(openList, nx, ny);

			if (!neighbor)
			{
				neighbor = new Node{
					nx,
					ny,
					newG,
					heuristic(nx, ny, goal.x, goal.y),
					current
				};
				openList.push_back(neighbor);
			}
			else if (newG < neighbor->g)
			{
				neighbor->g = newG;
				neighbor->parent = current;
			}
		}
	}

	// Cleanup memory
	for (Node* n : openList) delete n;
	for (Node* n : closedList) delete n;

	return path;
}

SDL_Point Map::getNextStep(SDL_Point enemy, SDL_Point player)
{
	vector<SDL_Point> path = findPath(enemy, player);
	//cout << "path size " << path.size() << endl;

	if (path.size() >= 2)
	{		
		cout << "update path\n";
		//int random = rand() % (path.size() - 1);
		return path[1];
	}
	return enemy;
}





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
	loadMap();

	src.x = src.y = 0;
	src.w = dest.w = TILE;
	src.h = dest.h = TILE;


	dest.x = 0;
	dest.y = 0;
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

	loadMap();

	src.x = src.y = 0;
	src.w = dest.w = TILE;
	src.h = dest.h = TILE;


	dest.x = 0;
	dest.y = MAP_OFFSET_Y;
}

void Map::updateGraph(int xpos, int ypos)
{
	int currRow = xpos % TILE;
	int currCol = ypos % TILE;
	
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
			if (type == 1 || type == 3 || type == 4)//dug			
				map.setWalkable(col, row, true);
			
			else
				map.setWalkable(col, row, false);
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
			
			dest.x = j * TILE;
			dest.y = MAP_OFFSET_Y + i * TILE;
			
			evaluateTile(type);
		}
	}
}

void Map::digTile(int x, int y, int direction, int& points)
{
	//TRICK FOR DIGGER DIGGING AND LOOKING LIKE HE IS DIGGING IN THE RIGHT PLACE
	int tilePosX = (x + 32)  / TILE;
	int tilePosY = (y - 32) / TILE;

	std::cout << "DUG TILE: "
		<< tilePosX << ","
		<< tilePosY << std::endl;



	if (tiles[tilePosY][tilePosX] != 4) 
	{
		//horizontal movement and 
		if ((direction == 3 || direction == 4) && tiles[tilePosY][tilePosX] == 1)
		{
			tiles[tilePosY][tilePosX] = 4;
			map.setWalkable(tilePosX, tilePosY, true);
			//cout << "Horizontal movement" << direction << endl;
			return;
		}
		//vertival movement and horizontal tile
		if ((direction == 1 || direction == 2) && tiles[tilePosY][tilePosX] == 3)
		{
			tiles[tilePosY][tilePosX] = 4;
			map.setWalkable(tilePosX, tilePosY, true);
			//cout << "Vertical movement:" << direction << endl;
			return;
		}

		if (tiles[tilePosY][tilePosX] == 4) return;

		if (direction == 1 || direction == 2)//vertical
		{
			//collect emerald
			if (tiles[tilePosY][tilePosX] == 2) points += 25;
			tiles[tilePosY][tilePosX] = 1;
			map.setWalkable(tilePosX, tilePosY, true);
		}

		if (direction == 3 || direction == 4) // horizontal
		{
			//collect emerald
			if (tiles[tilePosY][tilePosX] == 2) points += 25;
			tiles[tilePosY][tilePosX] = 3; 
			map.setWalkable(tilePosX, tilePosY, true);
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

