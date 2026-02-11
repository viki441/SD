#pragma once
#include "GameObject.h"

//enum class Status
//{
//	ALIVE, CHASING, WANDERING, FLEEING, DEAD, DIGGING
//};

class Enemy : public GameObject
{

public:
	Enemy(int x, int y, SDL_Texture* tex);

	void update() override;
	void render(SDL_Renderer* renderer) override;
	void dig(Map& map) override;
	void changeAnimation(Direction direction) override;
	
	~Enemy() override
	{
		SDL_DestroyTexture(objTexture);
	}
	
	const Direction getDirection() const;
	const int getNextX() const;
	const int getNextY() const;
	const bool hasTargetNow() const;



	void chase(Map& map, int playerX, int playerY);



	void requestPath();
	void moveAlongPath(float dt);


private:
	int dx = 0;
	int dy = 0;
	double speed = 0.5;

	int frameCount = 3;
	bool isHobbin = false;
	bool hasTarget = false;
	SDL_Point targetCoordinates;

};
