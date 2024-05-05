#include "EarthGunnery.h"
#include "../../Game/Game.h"

EarthGunnery::EarthGunnery(int p, int h, int c, Game* g) : Units(earthGunnery, p, h, c, g)
{
	id = eID;
}

bool EarthGunnery::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	bool Attacker = true;
	int i = 0;

	if (game->getUnit(alienMonster, enemy))
	{
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
		++i;
	}
	else if (game->getUnit(alienDrone, enemy))
	{
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
		++i;
	}

	while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienDrone)))
	{
		if (game->getUnit(alienMonster, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);

			if (Attacker)
			{
				game->toLog(this->getID(), enemy->getID());
				Attacker = false;
			}
			else
			{
				game->toLog(enemy->getID());
			}

			++i;
		}
		if (game->getUnit(alienDrone, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);

			if (Attacker)
			{
				game->toLog(this->getID(), enemy->getID());
				Attacker = false;
			}
			else
			{
				game->toLog(enemy->getID());
			}
			++i;
		}
		if (game->getUnit(alienMonster, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);

			if (Attacker)
			{
				game->toLog(this->getID(), enemy->getID());
				Attacker = false;
			}
			else
			{
				game->toLog(enemy->getID());
			}

			++i;
		}
	}
	if (!Attacker)
	{
		Attacker = true;
		game->toLog();
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
		{
			game->kill(enemy);
			game->updateFile(enemy);
		}
		else
			game->addUnit(enemy);
	}
	return true;
}