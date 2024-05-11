#include "EarthHeal.h"
#include "../../Game/Game.h"

EarthHeal::EarthHeal(int p, int h, int c, Game* g) : Units(earthHeal, p, h, c, g)
{
	id = eID;
}

bool EarthHeal::attack()
{
	Units* ally = nullptr;
 	bool healed = false;
	LinkedQueue<Units*> temp;

	for (int i = 0; i < getAttackCap(); i++)
	{
		if (game->getUML(ally))
		{
			if ((game->getTimestep() - ally->getUMLtime()) < 10)
			{
				ally->getAttacked(-(getPower() * getHealth() / 100));

				if (!ally->isHealed())
					ally->heal();

				if (ally->getHealthPerc() > 20)
					game->addUnit(ally);
				else
					temp.enqueue(ally);
				if (!healed)
				{
					game->toLog(this->getID(), ally->getID(), "EH");
					healed = true;
				}
				else
					game->toLog(ally->getID());
			}
			else
			{
				ally->getAttacked(pow(ally->getCurHealth(), 2));
				game->kill(ally);
				--i;
			}
		}
	}	

	while (temp.dequeue(ally))
		game->toUML(ally);

	if (healed)
	{
		Units* heal;
		game->toLog();
		game->getUnit(earthHeal, heal);
		heal->setTa(game->getTimestep());
		heal->getAttacked(pow(heal->getCurHealth(), 2));
		game->kill(heal);
	}
	return healed;
}