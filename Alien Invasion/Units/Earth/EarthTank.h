#ifndef	EARTH_TANK_H
#define EARTH_TANK_H
#include "../Units.h"

class EarthTank : public Units
{

public:
	EarthTank(int, int, int, int);
	
	bool Attack();

	bool GetAttacked();

	bool IsDead();
};
#endif