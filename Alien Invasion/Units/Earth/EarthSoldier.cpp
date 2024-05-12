#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g)
{
	id = eID;
}

bool EarthSoldier::attack()
{
	Units* enemy = nullptr;
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
				game->toLog("ES", this->getID(), enemy->getID());
				attacked = true;
			}
			else
			{
				game->toLog("ET", enemy->getID());
			}
		}
	}
	if (attacked)
		game->toLog();
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
		{
			game->kill(enemy);
		}
		else
			game->addUnit(enemy);
	}
	return attacked;
}