#include "AlienDrone.h"
#include "../../Game/Game.h"

AlienDrone::AlienDrone(int p, int h, int c, Game* g) : Units(alienDrone, p, h, c, g) 
{
	id = aID;
}

bool AlienDrone::attack()
{
	return false;
}

bool AlienDrone::getAttacked()
{
	return false;
}

bool AlienDrone::isDead()
{
	return this->getCurHealth() == 0;
}
