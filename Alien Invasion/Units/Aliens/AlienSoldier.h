#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H
#include "../Units.h"

class AlienSoldier : public Units
{

public:
	AlienSoldier(int, int, int, int);
	
	bool Attack();

	bool GetAttacked();

	bool IsDead();
};

#endif