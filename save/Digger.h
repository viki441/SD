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
	
	const Direction getDirection() const;
	
	void updateDirection(const Uint8* keystate);
	const int getNextX() const;
	const int getNextY() const;
	

	~Digger() override
	{
		SDL_DestroyTexture(objTexture);
	}

private:

	int dx = 10;
	int dy = 10;

	int frameCount = 4;

};