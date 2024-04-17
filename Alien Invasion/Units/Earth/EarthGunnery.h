#ifndef	EARTH_GUNNERY_H
#define EARTH_GUNNERY_H
#include "../Units.h"

class EarthGunnery: public Units
{

public:
	EarthGunnery(int p, int h, int c, int timestep);
	
	bool Attack();

	bool GetAttacked();

	bool IsDead();

};
#endif