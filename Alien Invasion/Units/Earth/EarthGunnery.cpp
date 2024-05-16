#include "EarthGunnery.h"
#include "../../Game/Game.h"

EarthGunnery::EarthGunnery(int p, int h, int c, Game* g) : Unit(earthGunnery, p, h, c, g)
{
	id = eID;
}

bool EarthGunnery::attack()
{
	Unit* enemy = nullptr;
	Unit* self = this;
	LinkedQueue<Unit*> temp;
	bool attacked = false;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienDrone)))
	{
		if (game->getUnit(alienMonster, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);
			++i;

			if (!attacked)
			{
				game->toLog(self , enemy);
				attacked = true;	//EG shots
			}
			else
				game->toLog(enemy);
		}

		if (i == getAttackCap())			// Checks whether it has reached its maximum attack capacity
			break;

		if (game->getUnit(alienDrone, enemy))
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

		if (i == getAttackCap())			// Checks whether it has reached its maximum attack capacity
			break;

		if (game->getUnit(alienDrone, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);
			++i;

			game->toLog(enemy);
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