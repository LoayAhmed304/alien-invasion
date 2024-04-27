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
	bool Attacker = true;

	if (game->getLength(earthSoldier) < (game->getLength(alienSoldier) * .3))
	{
		int i = 0;
		while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienSoldier)))
		{
			if (game->getUnit(alienSoldier, enemy))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;
				if (Attacker)
				{
					game->totemp(this);
					Attacker = false;
				}
				game->totemp(enemy);
			}
			if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				game->totemp(enemy);
				++i;
				if (Attacker)
				{
					game->totemp(this);
					Attacker = false;
				}
				game->totemp(enemy);
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
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				if (Attacker)
				{
					game->totemp(this);
					Attacker = false;
				}
				game->totemp(enemy);
			}
			else
				break;
		}
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
		{
			game->kill(enemy);
			game->updateFile(enemy);
		}
		else
			game->addUnit(enemy);

		if (!Attacker)
		{
			game->totemp(nullptr);
			Attacker = true;
		}
	}

	return true;
}