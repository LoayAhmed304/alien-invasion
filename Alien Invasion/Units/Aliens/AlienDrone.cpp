#include "AlienDrone.h"
#include "../../Game/Game.h"

AlienDrone::AlienDrone(int p, int h, int c, Game* g) : Unit(alienDrone, p, h, c, g) 
{
	id = aID;
}

bool AlienDrone::attack()
{
	Unit* enemy = nullptr;
	Unit* self = this;
	LinkedQueue<Unit*> temp;
	bool attacked = false;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(earthTank) || !game->isEmpty(earthGunnery)))
	{
		if (game->getUnit(earthTank, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);
			++i;

			if (!attacked)
			{
				game->toLog(self, enemy);
				attacked = true;
			}
			else
				game->toLog(enemy);
		}

		if (i == getAttackCap())			// Checks whether it has exceeded its maximum attack capacity
			break;

		if (game->getUnit(earthGunnery, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);
			++i;

			if (!attacked)
			{
				game->toLog(self, enemy);
				attacked = true;
			}
			else
				game->toLog(enemy);
		}
	}

	if (attacked)
		game->toLog();

	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else if (enemy->getType() == earthTank && enemy->getHealthPerc() < 20)
			game->toUML(enemy);
		else
			game->addUnit(enemy);
	}

	return attacked;
}