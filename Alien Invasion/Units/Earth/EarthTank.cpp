#include "EarthTank.h"
#include "../../Game/Game.h"

EarthTank::EarthTank(int p, int h, int c, Game* g) : Units(earthTank, p, h, c, g) 
{
	id = eID;
}

bool EarthTank::attack()
{
	return true;
}

bool EarthTank::getAttacked()
{
	return false;
}

bool EarthTank::isDead()
{
	return this->getCurHealth() == 0;
}
