#include "AlienDrone.h"
#include "../../Game/Game.h"

AlienDrone::AlienDrone(int p, int h, int c, Game* g) : Units(alienDrone, p, h, c, g) 
{
	id = aID;
}

bool AlienDrone::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	bool Attacker = true;
	int i = 0;
	if (game->getUnit(earthTank, enemy))
	{
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
		++i;
	}
	else if (game->getUnit(earthGunnery, enemy))
	{
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
		++i;
	}
	while (i < getAttackCap() && (!game->isEmpty(earthTank) || !game->isEmpty(earthGunnery)))
	{
		if (game->getUnit(earthGunnery, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;

			if (Attacker)
			{
				game->toLog(this->getID(), enemy->getID());
				Attacker = false;
			}
			else
			{
				game->toLog(enemy->getID());
			}

		}
		if (game->getUnit(earthTank, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;

			if (Attacker)
			{
				game->toLog(this->getID(), enemy->getID());
				Attacker = false;
			}
			else
			{
				game->toLog(enemy->getID());
			}

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
		else if (enemy->getType() == earthTank && enemy->getHealthPerc() < 20)
			game->toUML(enemy);
		else
			game->addUnit(enemy);
	}
	return true;
}