#include <iostream>
#include <deque> // for removing and adding

#include "Constants.h"

#include <SDL.h>
#include <SDL_image.h>


using namespace std;

class Entity
{
protected:
	
	//hp just for the digger, enemies have 1hp
	struct Coordinates
	{
		int x;
		int y;

		Coordinates(int xCorrd, int yCoord)
			:x(xCorrd), y(yCoord) {};
	};

	Coordinates coordinates;
	SDL_Texture* texture; // image
	


public:
	//Entity();
	Entity(Coordinates c, SDL_Texture* t); 

	virtual ~Entity() = default; // see theory

	virtual void update(double deltaTime) = 0;//what is deltatime?
	virtual void render(SDL_Renderer* renderer) = 0;

	
	
	int getX() const
	{
		return coordinates.x;
	}
	int getY() const
	{
		return coordinates.y;
	}
	SDL_Rect getRect() const;
	bool isAlive() const; //checks if state is dead



};
