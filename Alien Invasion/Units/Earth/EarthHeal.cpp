#include "EarthHeal.h"
#include "../../Game/Game.h"

EarthHeal::EarthHeal(int p, int h, int c, Game* g) : Unit(earthHeal, p, h, c, g)
{
	id = eID;
}

bool EarthHeal::attack()
{
	Unit* ally = nullptr;
	Unit* self = this;
 	bool healed = false;
	LinkedQueue<Unit*> temp;
	for (int i = 0; i < getAttackCap(); i++)
	{

		if (game->getUML(ally))
		{
			if ((game->getTimestep() - ally->getUMLtime()) < 10)
			{
				if(ally->getHealthPerc() < 20)
				{
					ally->getAttacked(-self->UAP(ally));
					ally->incHT();
					if (!ally->isHealed())
						ally->heal();

					if (ally->getHealthPerc() > 20)
					{
						if (ally->isInfected())
						{
							temp.enqueue(ally);
						}
						else
							game->addUnit(ally);
					}
					else
						temp.enqueue(ally);
					if (!healed)
					{
						game->toLog(self, ally);
						healed = true;
					}
					else
						game->toLog(ally);
				}
				else
				{
					if (ally->getHT() > 0)
					{
						ally->setHT(ally->getHT() - 1);
						game->toUML(ally);
					}
					else
					{
						if (!healed)
						{
							game->toLog(self, ally);
							healed = true;
						}
						else
							game->toLog(ally);
						ally->removeInfected();
						ally->getCured();
						game->addUnit(ally);
					}
				}
			}
			else
			{
				ally->getAttacked(ally->getCurHealth());
				game->kill(ally);
				--i;
			}
		}
	}	

	while (temp.dequeue(ally))
		game->toUML(ally);

	if (healed)
	{
		game->toLog();
		game->getUnit(earthHeal, self);
		self->setTa(game->getTimestep());
		self->getAttacked(self->getCurHealth());
		game->kill(self);
	}

	return healed;
}