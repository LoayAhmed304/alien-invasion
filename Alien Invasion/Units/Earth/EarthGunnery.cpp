#include "EarthGunnery.h"
#include "../../Game.h"

EarthGunnery::EarthGunnery(int p, int h, int c, Game* g) : Units(earthGunnery, p, h, c, g)
{
	id = eID;
}

bool EarthGunnery::attack()
{
	return false;
}

bool EarthGunnery::getAttacked()
{
	return false;
}

bool EarthGunnery::isDead()
{
	return false;
}
