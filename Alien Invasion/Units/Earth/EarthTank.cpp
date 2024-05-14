#include "EarthTank.h"
#include "../../Game/Game.h"

EarthTank::EarthTank(int p, int h, int c, Game* g) : Units(earthTank, p, h, c, g) 
{
	id = eID;
}

bool EarthTank::attack()
{
	Units* enemy = nullptr;
	Units* self = this;
	LinkedQueue<Units*> temp;
	bool attacked = false;
	int i = 0;

	if (game->getLength(earthSoldier) < float(game->getLength(alienSoldier) * .3))
	{
		while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienSoldier)))
		{
			if (game->getUnit(alienSoldier, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
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

			if (game->getUnit(alienMonster, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;

				if (!attacked)
				{
					game->toLog(this, enemy);
					attacked = true;
				}
				else
					game->toLog(enemy);
			}
		}
	}
	else
	{
		for (int i = 0; i < getAttackCap(); ++i)
		{
			if (game->getUnit(alienMonster, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);

				if (!attacked)
				{
					game->toLog(self, enemy);
					attacked = true;
				}
				else
					game->toLog(enemy);
			}
			else
				break;
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