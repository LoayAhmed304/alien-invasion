#include "EarthHeal.h"
#include "../../Game/Game.h"

EarthHeal::EarthHeal(int p, int h, int c, Game* g) : Units(earthHeal, p, h, c, g)
{
	id = eID;
}

bool EarthHeal::attack()
{
	Units* ally = nullptr;
 	bool die = false;
	LinkedQueue<Units*> temp;

	for (int i = 0; i < getAttackCap(); i++)
	{
		if (game->getUML(ally))
		{
			if ((game->getTimestep() - ally->getUMLtime()) < 10)
			{
				ally->getAttacked(-(getPower() * getHealth() / 100));

				if (ally->getHealthPerc() > 20)
					game->addUnit(ally);
				else
					temp.enqueue(ally);
				
				die = true;
			}
			else
			{
				ally->getAttacked(ally->getCurHealth() * ally->getCurHealth());
				game->kill(ally);
			}
		}
	}

	while (temp.dequeue(ally))
		game->toUML(ally);

	if (die)
	{
		Units* heal;
		game->getUnit(earthHeal, heal);
		heal->getAttacked(getCurHealth() * getCurHealth());
		game->kill(heal);
	}
	return true;
}
