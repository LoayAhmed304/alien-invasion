#include "EarthTank.h"

EarthTank::EarthTank(int p, int h, int c, int timestep) : Units(earthTank, p, h, c, timestep)
{
	id = eID;
}

bool EarthTank::Attack()
{
	return false;
}

bool EarthTank::GetAttacked()
{
	return false;
}

bool EarthTank::IsDead()
{
	return false;
}
