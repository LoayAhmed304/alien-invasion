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
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
			{
				enemy->setTa(game->getTimestep());
				enemy->setDf(enemy->getTa() - enemy->getTj());
			}
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
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
		else
			game->addUnit(enemy);
	}
	return true;
}