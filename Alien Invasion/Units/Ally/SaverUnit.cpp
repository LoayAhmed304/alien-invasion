#include "SaverUnit.h"
#include "../../Game/Game.h"

SaverUnit::SaverUnit(int p, int h, int c, Game* g) : Unit(saverUnit, p, h, c, g)
{
	id = sID;
}

bool SaverUnit::attack()
{
	Unit* enemy = nullptr;
	Unit* self = this;
	LinkedQueue<Unit*> temp;
	bool attacked = false;
	for (int i = 0; i < this->getAttackCap(); ++i)
	{
		if (game->getUnit(alienSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);

			if (!attacked)
			{
				game->toLog(self, enemy);
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
		else
			game->addUnit(enemy);
	}

	return attacked;
}