#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <queue>

#include "Enemy.h"
#include "Digger.h"

using namespace std;
class Game
{

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	queue<Enemy> enemies;
	unsigned int level;
	unsigned int emerawds;
	bool isRunning = true;

	SDL_Texture* diggerTexture = nullptr;
	SDL_Texture* nobbinTexture = nullptr;
	SDL_Texture* hobbinTexture = nullptr;

	Digger* player = nullptr;



private:
	void processInput();
	void update(double dt);
	void render();


public:
	Game();
	~Game();
	void run();



};