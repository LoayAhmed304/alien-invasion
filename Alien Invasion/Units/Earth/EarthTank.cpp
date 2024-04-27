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
	bool attacked = false;

	if (game->getLength(earthSoldier) < (game->getLength(alienSoldier) * .3))
	{
		int i = 0;

		if (!game->isEmpty(alienMonster) || !game->isEmpty(alienSoldier))
		{
			attacked = true;
			cout << "ET " << getID() << " shots [";
		}

		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		else if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}

		while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienSoldier)))
		{
			if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				cout << ", ";
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;
			}
			if (game->getUnit(alienSoldier, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				cout << ", ";
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;
			}
		}
	}
	else
	{
		if (!game->isEmpty(alienMonster))
		{
			attacked = true;
			cout << "ET " << getID() << " shots [";
		}

		if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
		}

		for (int i = 1; i < getAttackCap(); ++i)
		{
			if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				cout << ", ";
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
			game->addUnit(enemy);
	}

	if (attacked)
	{
		cout << "]\n";
		return true;
	}
	return false;
}