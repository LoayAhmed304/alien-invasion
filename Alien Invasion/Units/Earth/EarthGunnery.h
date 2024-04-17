#ifndef	EARTH_GUNNERY_H
#define EARTH_GUNNERY_H
#include "../Units.h"

class EarthGunnery: public Units
{

public:
	EarthGunnery(int, int, int, int);
	
	bool Attack();

	bool GetAttacked();

	bool IsDead();

};
#endif