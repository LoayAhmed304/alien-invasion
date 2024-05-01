#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g)
{
	id = eID;
}

bool EarthSoldier::attack(string &log)
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	bool Attacker = true;
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(alienSoldier, enemy))
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
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead()) 
			game->kill(enemy);
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