#include "AlienMonster.h"
#include "../../Game/Game.h"

AlienMonster::AlienMonster(int p, int h, int c, Game* g) : Units(alienMonster, p, h, c, g)
{
	id = aID;
}

bool AlienMonster::attack()
{
	return false;
}

bool AlienMonster::getAttacked()
{
	return false;
}

bool AlienMonster::isDead()
{
	return this->getCurHealth() == 0;
}

