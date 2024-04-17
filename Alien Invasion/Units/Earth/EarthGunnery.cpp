#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int p, int h, int c, int timestep) : Units(earthGunnery, p, h, c, timestep) 
{
	id = eID;
}

bool EarthGunnery::Attack()
{
	return false;
}

bool EarthGunnery::GetAttacked()
{
	return false;
}

bool EarthGunnery::IsDead()
{
	return false;
}
