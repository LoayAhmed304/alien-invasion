#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H
#include "../Units.h"

class AlienMonster : public Units
{

public:
	AlienMonster(int p, int h, int c, int timestep);

	bool Attack();

	bool GetAttacked();

	bool IsDead();
};

#endif