#include "EarthTank.h"
#include "../../Game/Game.h"

EarthTank::EarthTank(int p, int h, int c, Game* g) : Units(earthTank, p, h, c, g) 
{
	id = eID;
}

bool EarthTank::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	if (game->getLength(earthSoldier) < (game->getLength(alienSoldier) * .3))
	{
		int i = 0;
		while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienSoldier)))
		{
			if (game->getUnit(alienSoldier, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				cout << "unit with id: " << id << " shot with dmg: ";
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;
			}
			if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				cout << "unit with id: " << id << " shot with dmg: ";
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;
			}
		}
	}
	else
	{
		for (int i = 0; i < getAttackCap(); ++i)
		{
			if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				cout << "unit with id: " << id << " shot with dmg: ";
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
			}
			else
				break;
		}
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else
			game->getAlienArmy()->addUnit(enemy);
	}
	return true;
}