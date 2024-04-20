#include "EarthHeal.h"
#include "../../Game.h"

EarthHeal::EarthHeal(int p, int h, int c, Game* g) : Units(earthHeal, p, h, c, g)
{
	id = eID;
}

bool EarthHeal::attack()
{
	Units* ally;
	bool die = false;
	int c = getAttackCap();

	for (int i = 0; i < c; i++)
	{
		if (game->getUML(ally))
		{
			if (ally->getUMLtime() < 10)
			{
				ally->getAttacked(-(getPower() * getHealth() / 100) / sqrt(ally->getHealth()));
				die = true;
			}
			else
			{
				ally->getAttacked(ally->getCurHealth());
				c++;
			}
		}
	}
	if (die)
	{
		Units* heal;
		game->getUnit(earthHeal, heal);
		heal->getAttacked(getCurHealth());
	}
	return true;
}

bool EarthHeal::getAttacked()
{
	return true;
}

bool EarthHeal::isDead()
{
	return false;
}
