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
	while (i < getAttackCap() && (!game->isEmpty(earthTank) || !game->isEmpty(earthGunnery)))
	{
		if (game->getUnit(earthTank, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
			if (Attacker)
			{
				game->totemp(this);
				Attacker = false;
			}
			game->totemp(enemy);

		}
		if (game->getUnit(earthGunnery, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
			if (Attacker)
			{
				game->totemp(this);
				Attacker = false;
			}
			game->totemp(enemy);

		}
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
		if (!Attacker)
		{
			game->totemp(nullptr);
			Attacker = true;
		}
	}

	return true;
}