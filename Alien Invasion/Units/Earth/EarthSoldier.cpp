#include "EarthSoldier.h"
#include "../../Game/Game.h"

EarthSoldier::EarthSoldier(int p, int h, int c, Game* g) : Units(earthSoldier, p, h, c, g)
{
	id = eID;
}

bool EarthSoldier::attack()
{
	Units* enemy;
	Units* unit = nullptr;

	for (int i = 0; i < getAttackCap(); i++)
	{
		if (game->getUnit(alienSoldier, enemy))
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
	}
	return true;
}