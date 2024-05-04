#include "EarthGunnery.h"
#include "../../Game/Game.h"

EarthGunnery::EarthGunnery(int p, int h, int c, Game* g) : Units(earthGunnery, p, h, c, g)
{
	id = eID;
}

bool EarthGunnery::attack(string& log)
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	bool Attacker = true;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienDrone)))
	{
		if (game->getUnit(alienMonster, enemy))
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

			++i;
		}
		if (game->getUnit(alienDrone, enemy))
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
			++i;
		}
		if (game->getUnit(alienDrone, enemy))
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

			++i;
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