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

private:
	int dx = 0;
	int dy = 0;


};
