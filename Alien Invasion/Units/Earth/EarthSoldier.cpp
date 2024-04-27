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

	if (game->getUnit(alienSoldier, enemy))
	{
		attacked = true;
		cout << "ES " << getID() << " shots [";
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
	}

	for (int i = 1; i < getAttackCap(); ++i)
	{
		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			cout << ", ";
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

	if (attacked)
	{
		cout << "]\n";
		return true;
	}
	return false;
}