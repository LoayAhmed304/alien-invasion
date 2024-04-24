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
		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
		}
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else
			game->addUnit(enemy);
	}
	return true;
}
