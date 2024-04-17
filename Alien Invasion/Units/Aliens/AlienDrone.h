#ifndef	ALIEND_DRONE_H
#define ALIEND_DRONE_H
#include "../Units.h"

class AlienDrone : public Units
{

public:
	AlienDrone(int, int, int, int);

	bool Attack();

	bool GetAttacked();

	bool IsDead();
};
#endif