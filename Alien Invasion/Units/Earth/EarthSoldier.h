#ifndef	EARTH_SOLDIER_H
#define EARTH_SOLDIER_H
#include "../Units.h"

class EarthSoldier: public Units
{

public:
	EarthSoldier(int, int, int, int);

	bool Attack();

	bool GetAttacked();

	bool IsDead();
};
#endif