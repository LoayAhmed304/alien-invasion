#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H
#include "../Units.h"

class AlienMonster : public Units
{

public:
	AlienMonster(int, int, int, int);

	bool Attack();

	bool GetAttacked();

	bool IsDead();
};

#endif