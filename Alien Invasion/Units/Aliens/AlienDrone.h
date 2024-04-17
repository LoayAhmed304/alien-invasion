#ifndef	ALIEND_DRONE_H
#define ALIEND_DRONE_H
#include "../Units.h"

class AlienDrone : public Units
{

public:
	AlienDrone(int p, int h, int c, int timestep);

	bool Attack();

	bool GetAttacked();

	bool IsDead();
};
#endif