#include "AlienSoldier.h"
#include "../../Game/Game.h"

AlienSoldier::AlienSoldier(int p, int h, int c, Game* g) : Units(alienSoldier, p, h, c, g)
{
	id = aID;
}

bool AlienSoldier::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(earthSoldier, enemy))
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
		}
		else if (enemy->getHealthPerc() < 20)
			game->toUML(enemy);
		else
			game->addUnit(enemy);
	}
	return true;
}
