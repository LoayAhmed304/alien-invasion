#include "AlienSoldier.h"
#include "../../Game.h"

AlienSoldier::AlienSoldier(int p, int h, int c, Game* g) : Units(alienSoldier, p, h, c, g)
{
	id = aID;
}

bool AlienSoldier::getAttacked()
{
	return false;
}

bool AlienSoldier::isDead()
{
	return false;
}

bool AlienSoldier::attack()
{
	Units* enemy;
	Units* unit = nullptr;

	for (int i = 0; i < getAttackCap(); i++)
	{
		if (game->getUnit(earthSoldier, enemy))
		{
			enemy->getAttacked(getPower());
		}
	}
	return true;
}
