#pragma once
#include "Entity.h"


class Digger : public Entity
{
private:
	enum class State : unsigned int
	{
		DIG,
		SHOOT,
		CHASE //when cherry
	};

	State state = State::DIG;
	unsigned int points;
	double gunCooldown;
	unsigned int lives;



public:

	//-----------------------------------------OVERRIDE
	void update(double deltaTime) override;
	void render(SDL_Renderer* renderer) override;



	//-----------------------------------------LOCAL
	Digger(Coordinates c, SDL_Texture* t);
	~Digger();


	void shoot();


	//create hero
	


};