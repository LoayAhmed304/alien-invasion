#ifndef	EARTH_TANK_H
#define EARTH_TANK_H
#include "../Units.h"

class EarthTank : public Units
{

public:
	EarthTank(int p, int h, int c, int timestep);
	
	bool Attack();

	bool GetAttacked();

	bool IsDead();
};
#endif