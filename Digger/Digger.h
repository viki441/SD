#pragma once
#include "GameObject.h"

//enum class Status
//{
//	ALIVE, CHASING, DEAD
//};



class Digger : public GameObject
{
public:
	Digger(int x, int y, SDL_Texture* tex);

	void update() override;
	void render(SDL_Renderer* renderer) override;
	void dig(Map& map) override;
	void changeAnimation(Direction direction) override;
	
	



	void updateDirection(const Uint8* keystate);

	

//-----------------------------------------------------------GETTER AND SETTERS--------------------------------------------------------------------------

	const int getNextX() const;
	const int getNextY() const;
	const Direction getDirection() const;
	const int getPoints() const;
	const int getTileX() const;
	const int getTileY() const;



	~Digger() override
	{
		SDL_DestroyTexture(objTexture);
	}

private:

	int dx = 10;
	int dy = 10;
	int points;
	int frameCount = 4;
	

};