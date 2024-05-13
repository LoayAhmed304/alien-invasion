#include "AlienDrone.h"
#include "../../Game/Game.h"

AlienDrone::AlienDrone(int p, int h, int c, Game* g) : Units(alienDrone, p, h, c, g) 
{
	id = aID;
}

bool AlienDrone::attack()
{
	Units* enemy = nullptr;
	Units* unit = this;
	LinkedQueue<Units*> temp;
	bool attacked = false;
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

			if (!attacked)
			{
				game->toLog(unit, enemy);
				attacked = true;
			}
			else
				game->toLog(enemy);
		}
		if (game->getUnit(earthGunnery, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;

			if (!attacked)
			{
				game->toLog(unit, enemy);
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