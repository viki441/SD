#include "Game.h"
#include <stdexcept>

Game::Game() 
{
	//window creation
	window = SDL_CreateWindow("DiggerButBetter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window) throw runtime_error(SDL_GetError());
	//renderer creation
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) throw runtime_error(SDL_GetError());


	//textures
	//see digger class, maybe add a setter here?
	SDL_Texture* diggerTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\digger\\VRDIG1.bmp");
	SDL_Texture* hobbinTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\hobbin\\VRHOB1.bmp");
	SDL_Texture* nobbinTexture = IMG_LoadTexture(renderer, "C:\\Users\\vikik\\source\\repos\\DiggerButBetter\\assets\\images\\nobbin\\VNOB1.bmp");

	player = new Digger({ 100, 200 }, diggerTexture);
}

Game::~Game()
{
	delete player;
	SDL_DestroyTexture(diggerTexture);
	SDL_DestroyTexture(hobbinTexture);
	SDL_DestroyTexture(nobbinTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::run()
{
	SDL_Event;

	while (isRunning)
	{
		processInput();
		update(1.0 / 60.0);
		render();
	}
}


void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			isRunning = false;
	}
}


void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	player->render(renderer);
	SDL_RenderPresent(renderer);
		
}