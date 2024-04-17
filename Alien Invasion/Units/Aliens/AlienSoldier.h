#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H
#include "../Units.h"

#include "../Units.h"

class Game;

class AlienSoldier : public Units
{
public:
	AlienSoldier(int p, int h, int c, Game* g);
	bool attack();
	bool getAttacked();
	bool isDead();
};

#endif