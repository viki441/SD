#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <queue>


//ENEMMMMMMMMMMMMMMMMMMMTTYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY

bool Map::isWalkable(int x, int y)
{
	if (x < 0 || y < 0 || x >= COLS || y >= ROWS)
		return false;

	return this->map.isWalkable(y, x);

	
}

vector<SDL_Point> Map::findPath(SDL_Point start, SDL_Point goal)
{
	vector<SDL_Point> path;

	if (!isWalkable(goal.x, goal.y))
	{
		cout << "Path empty\n";
		return path;
	}
		

	// Grid to keep track of visited tiles
	vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
	// Grid to store the parent of each tile for path reconstruction
	vector<vector<SDL_Point>> parent(ROWS, vector<SDL_Point>(COLS, { -1, -1 }));

	queue<SDL_Point> q;
	q.push(start);
	visited[start.y][start.x] = true;

	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };

	bool found = false;

	while (!q.empty())
	{
		SDL_Point curr = q.front();
		q.pop();

		if (curr.x == goal.x && curr.y == goal.y)
		{
			found = true;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int nx = curr.x + dx[i];
			int ny = curr.y + dy[i];

			if (nx < 0 || ny < 0 || nx >= COLS || ny >= ROWS) continue;
			if (!isWalkable(nx, ny) || visited[ny][nx]) continue;

			visited[ny][nx] = true;
			parent[ny][nx] = curr;
			q.push({ nx, ny });
		}
	}

	if (!found) return path; // No path found

	// Reconstruct path from goal to start
	SDL_Point p = goal;
	while (p.x != -1)
	{
		path.push_back(p);
		p = parent[p.y][p.x];
	}

	std::reverse(path.begin(), path.end());
	return path;
}


SDL_Point Map::getNextStep(SDL_Point enemy, SDL_Point player)
{
	/*std::cout << "Enemy tile: " << enemy.x << "," << enemy.y
		<< " Walkable: " << map.isWalkable(enemy.x, enemy.y) << std::endl;
	std::cout << "Player tile: " << player.x << "," << player.y
		<< " Walkable: " << map.isWalkable(player.x, player.y) << std::endl;
	*/
	
	cout << "enemy position walkable? " << this->map.isWalkable(enemy.x, enemy.y)<< endl;


	std::vector<SDL_Point> path = findPath(enemy, player);
	if (path.size() >= 2) return path[1]; // Next tile
	return enemy;
	
	//int random = rand() % (path.size() - 1);
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
			if (type == 1 || type == 3 || type == 4)
			{
				this->map.setWalkable(col, row, true);
				/*if (row == 0 && col == 14)
				{
					cout << row << " " << col << endl;
					cout << "walkable: " << this->map.isWalkable(col, row);
				}*/
			}
			else
				this->map.setWalkable(col, row, false);
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

	/*std::cout << "DUG TILE: "
		<< tilePosX << ","
		<< tilePosY << std::endl;*/



	if (tiles[tilePosY][tilePosX] != 4) 
	{
		//horizontal movement and 
		if ((direction == 3 || direction == 4) && tiles[tilePosY][tilePosX] == 1)
		{
			tiles[tilePosY][tilePosX] = 4;
			this->map.setWalkable(tilePosX, tilePosY, true);
			//cout << "Horizontal movement" << direction << endl;
			return;
		}
		//vertival movement and horizontal tile
		if ((direction == 1 || direction == 2) && tiles[tilePosY][tilePosX] == 3)
		{
			tiles[tilePosY][tilePosX] = 4;
			this->map.setWalkable(tilePosX, tilePosY, true);
			//cout << "Vertical movement:" << direction << endl;
			return;
		}

		if (tiles[tilePosY][tilePosX] == 4) return;

		if (direction == 1 || direction == 2)//vertical
		{
			//collect emerald
			if (tiles[tilePosY][tilePosX] == 2) points += 25;
			tiles[tilePosY][tilePosX] = 1;
			this->map.setWalkable(tilePosX, tilePosY, true);
		}

		if (direction == 3 || direction == 4) // horizontal
		{
			//collect emerald
			if (tiles[tilePosY][tilePosX] == 2) points += 25;
			tiles[tilePosY][tilePosX] = 3; 
			this->map.setWalkable(tilePosX, tilePosY, true);
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

