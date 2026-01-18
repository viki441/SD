#include <iostream>
#include "Entity.h"

class Bag : public Entity
{
private:

	enum class State : unsigned int
	{
		FALL,STABLE,BROKEN
	};
	State state = State::STABLE;
	double fallTimer = 0.0;
	unsigned int points = 500; //if collected



public:
	//-----------------------------------------OVERRIDE
	void update(double deltaTime) override;
	void render(SDL_Renderer* renderer) override;


	//-----------------------------------------LOCAL
	void fall(double fallTimer);
	bool didKillEnemy();

};