#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int p, int h, int c, int timestep) : Units(earthSoldier, p, h, c, timestep) 
{
	id = eID;
}

bool EarthSoldier::Attack()
{
	return false;
}

bool EarthSoldier::GetAttacked()
{
	return false;
}

bool EarthSoldier::IsDead()
{
	return false;
}
