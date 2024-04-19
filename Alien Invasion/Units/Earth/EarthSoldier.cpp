#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g) 
{
	id = eID;
}

bool EarthSoldier::attack()
{
	Units* enemy;
	game->getUnit(alienSoldier, enemy);
	return true;
}

bool EarthSoldier::getAttacked()
{
	return true;
}

bool EarthSoldier::isDead()
{
	return false;
}
