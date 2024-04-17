#ifndef	EARTH_SOLDIER_H
#define EARTH_SOLDIER_H
#include "../Units.h"

class EarthSoldier: public Units
{

public:
	EarthSoldier(int p, int h, int c, int timestep);

	bool Attack();

	bool GetAttacked();

	bool IsDead();
};
#endif