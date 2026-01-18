/* NOTES FROM WALKTROUGH  https://youtu.be/DJTtG5m7ZwE?si=8hP28iOkcIXmPHzN
* If a bag of gold is falling on top of a monster, the monster starts falling with it too, if given correct path, it gets destroyed at the 'bottom' of the 'path'


2:27 - they dont really run away?
5:23 - hobbin can dig while is running away from player


**********CREATOR'S NOTES
* Gold (as in a broken bag) disappears very quickly if you dig underneath it.
* Monsters going up change direction when there is a bag falling on them, but they do the same thing even if the bag is below them in the same column.
*The program allocates enough resources for 6 monsters, but only 5 are on screen at any given time.
* 
* 
* NOTES UP TO LEVEL 10
* The number of times nobbins have to cross to become hobbins decreases.  <-which means the turning is not random and there should be some connection between the enemies
* The monsters move slightly faster on average (their speed is actually random). 
* 
* 
* 
*/


#include "Entity.h"

#include <SDL.h>
#include <SDL_image.h>

class Enemy : public Entity
{
private:

	enum class Type
	{
		NOBBIN, HOBBIN
	};
	enum class State : unsigned int 
	{
		WANDER, // for hobbin combines dig + something, 
		CHASE,
		AVOID_DANGER,
		DEAD
	};

	//has coord 
	Type type = Type::NOBBIN;
	State state = State::WANDER;

	unsigned int velocity;
	bool isDigging = false; //default is nobbin


public:
	//------------------------------------------OVERRIDE
	void update(double deltaTime) override;



	//------------------------------------------LOCAL
	void turnIntoHobbin();
	void runAway();
	bool canDig() const; //    return mode == Mode::HOBBIN;
	
	Enemy(Coordinates c, SDL_Texture* t);
	~Enemy();
	

};