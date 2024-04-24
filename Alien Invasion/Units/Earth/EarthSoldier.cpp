#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g)
{
	id = eID;
}

bool EarthSoldier::attack()
{
	LinkedQueue<Units*> tempList;
	Units* enemy = nullptr;
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			tempList.enqueue(enemy);
		}
	}
	while (tempList.dequeue(enemy))
	{
		if (enemy->isDead()) 
			game->kill(enemy);
		else
			game->getAlienArmy()->addUnit(enemy);
	}
	return true;
}