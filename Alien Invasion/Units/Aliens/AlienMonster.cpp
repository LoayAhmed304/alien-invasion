#include "AlienMonster.h"
#include "../../Game/Game.h"

AlienMonster::AlienMonster(int p, int h, int c, Game* g) : Unit(alienMonster, p, h, c, g)
{
	id = aID;
}

bool AlienMonster::attack()
{
	Unit* enemy = nullptr;
	Unit* self = this;
	string s;

	LinkedQueue<Unit*> temp;
	bool attacked = false;
	bool infects = false;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(earthSoldier) || !game->isEmpty(earthTank)))
	{
		if (game->getUnit(earthSoldier, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			if (!game->canInfect() || enemy->isInfected() || enemy->isCured())
			{
				enemy->getAttacked(self->UAP(enemy));
				if (!attacked)
				{
					game->toLog(self, enemy);
					attacked = true;
				}
				else
					game->toLog(enemy);
			}
			else 
			{
				enemy->getInfected();
				if (!infects)
				{
					s += "AM " + game->getColor("green") + to_string(self->getID()) + game->getColor("white") + " infects[" + game->getColor("blue") + to_string(enemy->getID());
					infects = true;
				}
				else
					s += game->getColor("white") + ", " + game->getColor("blue") + to_string(enemy->getID());
			}
			temp.enqueue(enemy);
			++i;
		}

		if (i == getAttackCap())			// Checks whether it has exceeded its maximum attack capacity
			break;

		if (game->getUnit(saverUnit, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);
			++i;

			if (!attacked)
			{
				game->toLog(self, enemy);
				attacked = true;
			}
			else
				game->toLog(enemy);
		}

		if (i == getAttackCap())			// Checks whether it has exceeded its maximum attack capacity
			break;

		if (game->getUnit(earthTank, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			enemy->getAttacked(self->UAP(enemy));
			temp.enqueue(enemy);
			++i;

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
	if (infects)
	{
		s+= game->getColor("white") + "]\n";
		game->toLog(nullptr,nullptr,s);
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else if (enemy->getHealthPerc() < 20 && enemy->getType() != saverUnit)
			game->toUML(enemy);
		else
			game->addUnit(enemy);
	}

	return attacked;
}