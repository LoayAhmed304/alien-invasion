#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int p, int h, int c, int timestep) : Units(alienSoldier, p, h, c, timestep)
{
	id = aID;
}

bool AlienSoldier::Attack()
{
	return false;
}

bool AlienSoldier::GetAttacked()
{
	return false;
}

bool AlienSoldier::IsDead()
{
	return false;
}
