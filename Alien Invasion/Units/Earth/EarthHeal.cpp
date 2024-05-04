#include "EarthHeal.h"
#include "../../Game/Game.h"

EarthHeal::EarthHeal(int p, int h, int c, Game* g) : Units(earthHeal, p, h, c, g)
{
	id = eID;
}

bool EarthHeal::attack(string& log)
{
	Units* ally;
	bool die = false;

	for (int i = 0; i < getAttackCap(); i++)
	{
		if (game->getUML(ally))
		{
			if (ally->getUMLtime() < 10)
			{
				ally->getAttacked(-(getPower() * getHealth() / 100));
				if (ally->getHealthPerc() > 20)
				{
					game->addUnit(ally);
				}
				else
				{
					game->toUML(ally);
				}
				die = true;
			}
			else
			{
				ally->getAttacked(pow(ally->getCurHealth(), 1.5));
				game->kill(ally);
				game->updateFile(ally);
				i--;
			}
		}
	}
	if (die)
	{
		Units* heal;
		game->getUnit(earthHeal, heal);
		heal->getAttacked(pow(heal->getCurHealth(), 1.5));
		game->kill(heal);
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