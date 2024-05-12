#include "AlienMonster.h"
#include "../../Game/Game.h"

AlienMonster::AlienMonster(int p, int h, int c, Game* g) : Units(alienMonster, p, h, c, g)
{
	id = aID;
}

bool AlienMonster::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	bool attacked = false;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(earthSoldier) || !game->isEmpty(earthTank)))
	{
		if (game->getUnit(earthSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			if (!game->canInfect() || enemy->isInfected() || enemy->isCured())
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			else
				enemy->getInfected();
			temp.enqueue(enemy);

			if (!attacked)
			{
				game->toLog("AM", this->getID(), enemy->getID());
				attacked = true;
			}
			else
				game->toLog("AM", enemy->getID());
			++i;
		}
		if (game->getUnit(earthTank, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);

			if (!attacked)
			{
				game->toLog("AM", this->getID(), enemy->getID());
				attacked = true;
			}
			else
				game->toLog("AM", enemy->getID());

			++i;
		}
	}
	if (attacked)
		game->toLog();
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else if (enemy->getHealthPerc() < 20)
			game->toUML(enemy);
		else
			game->addUnit(enemy);
	}
	return attacked;
}