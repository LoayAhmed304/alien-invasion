#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g)
{
	id = eID;
}

bool EarthSoldier::attack()
{
	Units* enemy = nullptr;
	Units* unit = this;
	LinkedQueue<Units*> temp;
	bool attacked = false;
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);

			if (!attacked)
			{
				game->toLog(unit, enemy);
				attacked = true;
			}
			else
			{
				game->toLog(enemy);
			}
		}
	}
	if (attacked)
		game->toLog();
	if (game->canSpread() && this->isInfected())
	{
		Units* toInfect = nullptr;
		if (game->getRandomES(toInfect) && (toInfect != this))
		{
			if (toInfect->getInfected())
			{
				game->toLog(unit, toInfect);
				game->toLog();
			}
		}
	}

	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else
			game->addUnit(enemy);
	}
	return attacked;
}