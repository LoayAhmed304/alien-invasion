#include "EarthSoldier.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g) 
{
	id = eID;
}

bool EarthSoldier::attack()
{
	Units* enemy;
	Units* unit = nullptr;

	for(int i =0 ; i < getAttackCap(); i++)
	{
		if (game->getUnit(alienSoldier, enemy))
		{
			enemy->getAttacked(getPower());
		}
	}
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
