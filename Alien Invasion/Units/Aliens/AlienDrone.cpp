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
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(earthTank) || !game->isEmpty(earthGunnery)))
	{
		if (game->getUnit(earthTank, enemy))
		{
			if (!enemy->getTa())
			{
				enemy->setTa(game->getTimestep());
				enemy->setDf(enemy->getTa() - enemy->getTj());
			}
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		if (game->getUnit(earthGunnery, enemy))
		{
			if (!enemy->getTa())
			{
				enemy->setTa(game->getTimestep());
				enemy->setDf(enemy->getTa() - enemy->getTj());
			}
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
		{
			enemy->setTd(game->getTimestep());
			enemy->setDd(enemy->getTd() - enemy->getTa());
			enemy->setDb(enemy->getDf() + enemy->getDd());
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