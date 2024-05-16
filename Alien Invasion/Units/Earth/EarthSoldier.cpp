#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Unit(earthSoldier, p, h, c, g)
{
	id = eID;
}

bool EarthSoldier::attack()
{
	Unit* enemy = nullptr;
	Unit* self = this;
	LinkedQueue<Unit*> temp;
	bool attacked = false;
	if (this->isInfected())
	{
		game->getUnit(earthSoldier, self);
		for (int i = 0; i < self->getAttackCap(); ++i)
		{
			if (game->getUnit(earthSoldier, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(self->UAP(enemy));
				temp.enqueue(enemy);

				if (!attacked)
				{
					game->toLog(self, enemy);
					attacked = true;
				}
				else
					game->toLog(enemy);
			}
		}
		game->addUnit(self);
	}
	else
	{
		for (int i = 0; i < this->getAttackCap(); ++i)
		{
			if (game->getUnit(alienSoldier, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(self->UAP(enemy));
				temp.enqueue(enemy);

				if (!attacked)
				{
					game->toLog(self, enemy);
					attacked = true;
				}
				else
					game->toLog(enemy);
			}
		}
	}
	if (attacked)
		game->toLog();

	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else
			game->addUnit(enemy);
	}

	return attacked;
}