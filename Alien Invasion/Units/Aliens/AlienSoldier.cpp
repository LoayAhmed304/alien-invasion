#include "AlienSoldier.h"
#include "../../Game/Game.h"

AlienSoldier::AlienSoldier(int p, int h, int c, Game* g) : Units(alienSoldier, p, h, c, g)
{
	id = aID;
}

bool AlienSoldier::attack()
{
	return false;
}
