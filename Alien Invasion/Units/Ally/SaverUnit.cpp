#include "SaverUnit.h"
#include "../../Game/Game.h"

SaverUnit::SaverUnit(int p, int h, int c, Game* g) : Units(saverUnit, p, h, c, g)
{
	id = sID;
}

bool SaverUnit::attack()
{
	Units* enemy = nullptr;
	Units* unit = this;
	LinkedQueue<Units*> temp;
	bool attacked = false;
	if (!game->getEarthArmy()->getinfCount())
	{
		while (!game->getAllyArmy()->isEmpty(alliedArmy))
			game->getAllyArmy()->getUnit(saverUnit,unit);
	}
	else
	{
		for (int i = 0; i < this->getAttackCap(); ++i)
		{
			if (game->getUnit(alienSoldier, enemy))
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
				{
					game->toLog(enemy);
				}
			}
		}
		if (attacked)
			game->toLog();
		while (temp.dequeue(enemy))
		{
			if (enemy->isDead())
			{
				game->kill(enemy);
			}
			else
				game->addUnit(enemy);
		}
	}
	return attacked;
}