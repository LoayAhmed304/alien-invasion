#include "EarthSaver.h"
#include "../../Game/Game.h"

EarthSaver::EarthSaver(int p, int h, int c, Game* g) : Units(earthSaver, p, h, c, g)
{
	id = eID;
}

bool EarthSaver::attack()
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
				game->toLog(this->getID(), enemy->getID());
				Attacker = false;
			}
			else
			{
				game->toLog(enemy->getID());
			}
		}
	}
	if (!Attacker)
	{
		Attacker = true;
		game->toLog();
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
		{
			game->kill(enemy);
		}
		else
			game->addUnit(enemy);
	}
	if (!game->getEarthArmy()->getInfectedCount())
	{
		if (game->getUnit(earthSaver, enemy));
		{
			enemy->getAttacked(pow(enemy->getCurHealth(), 1.5));
			enemy->setTa(game->getTimestep());
			game->kill(enemy);
		}
	}
	return true;
}