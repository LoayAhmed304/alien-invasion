#include "AlienSoldier.h"
#include "../../Game/Game.h"

AlienSoldier::AlienSoldier(int p, int h, int c, Game* g) : Units(alienSoldier, p, h, c, g)
{
	id = aID;
}

bool AlienSoldier::attack()
{
	Units* enemy = nullptr;
	Units* unit = this;
	LinkedQueue<Units*> temp;
	bool attacked = false;
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(earthSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);

			if (!attacked)
			{
				game->toLog(unit, enemy);
				attacked = true;
			}
			else
				game->toLog(enemy);

		}
	}
	if (attacked)
		game->toLog();
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else if (enemy->getHealthPerc() < 20)
			game->toUML(enemy);
		else
			game->addUnit(enemy);

	}
	return attacked;
}
