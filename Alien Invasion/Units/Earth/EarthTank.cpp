#include "EarthTank.h"
#include "../../Game/Game.h"

EarthTank::EarthTank(int p, int h, int c, Game* g) : Units(earthTank, p, h, c, g) 
{
	id = eID;
}

bool EarthTank::attack(string& log)
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
					log = log + to_string(this->getID()) + " shots [" + to_string(enemy->getID());
					Attacker = false;
				}
				else
				{
					log = log + ", " + to_string(enemy->getID());
				}
			}
			if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
			{
				if (!enemy->getTa())
					enemy->setTa(game->getTimestep());
				enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
				temp.enqueue(enemy);
				++i;

				if (Attacker)
				{
					log = log + to_string(this->getID()) + " shots [" + to_string(enemy->getID());
					Attacker = false;
				}
				else
				{
					log = log + ", " + to_string(enemy->getID());
				}
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
					log = log + to_string(this->getID()) + " shots [" + to_string(enemy->getID());
					Attacker = false;
				}
				else
				{
					log = log + ", " + to_string(enemy->getID());
				}
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
			Attacker = true;
			log = log + "]\n";
		}
	}

	return true;
}