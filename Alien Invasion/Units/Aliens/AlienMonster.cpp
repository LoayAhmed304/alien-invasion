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
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(earthSoldier) || !game->isEmpty(earthTank)))
	{
		if (game->getUnit(earthSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			cout << "unit with id: " << id << " shot with dmg: ";
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		if (game->getUnit(earthTank, enemy));
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			cout << "unit with id: " << id << " shot with dmg: ";
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else if (enemy->getHealthPerc() < 20)
			game->toUML(enemy);
		else
			game->getEarthArmy()->addUnit(enemy);
	}
	return true;
}