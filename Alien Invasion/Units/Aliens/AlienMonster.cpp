#include "AlienMonster.h"

AlienMonster::AlienMonster(int p, int h, int c, int timestep) : Units(alienMonster, p, h, c, timestep) 
{
	id = aID;
}

bool AlienMonster::Attack()
{
	return false;
}

bool AlienMonster::GetAttacked()
{
	return false;
}

bool AlienMonster::IsDead()
{
	return false;
}

