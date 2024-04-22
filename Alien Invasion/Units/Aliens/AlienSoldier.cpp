#include "AlienSoldier.h"
#include "../../Game/Game.h"

AlienSoldier::AlienSoldier(int p, int h, int c, Game* g) : Units(alienSoldier, p, h, c, g)
{
	id = aID;
}

bool AlienSoldier::attack()
{
	/*Units* enemy;
	Units* unit = nullptr;

	for (int i = 0; i < getAttackCap(); i++)
	{
		if (game->getUnit(earthSoldier, enemy))
		{
			enemy->getAttacked(getPower());
			if (enemy->getCurHealth() <= 0)
			{
				game->kill(enemy);
			}
			else if (enemy->getHealthPerc() < 20 && enemy->getHealthPerc() > 0)
			{
				game->toUML(enemy);
			}
			else
			{
				game->addUnit(enemy);
			}
		}
	}*/
	return true;
}
