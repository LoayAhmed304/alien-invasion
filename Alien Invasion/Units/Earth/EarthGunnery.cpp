#include "EarthGunnery.h"
#include "../../Game/Game.h"

EarthGunnery::EarthGunnery(int p, int h, int c, Game* g) : Units(earthGunnery, p, h, c, g)
{
	id = eID;
}

bool EarthGunnery::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	bool Attacker = true;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienDrone)))
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
				game->totemp(this);
				Attacker = false;
			}
			game->totemp(enemy);
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
				game->totemp(this);
				Attacker = false;
			}
			game->totemp(enemy);

			++i;
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
			game->totemp(nullptr);
			Attacker = true;
		}
	}

	return true;
}