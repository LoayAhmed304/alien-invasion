#ifndef	EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "../Units.h"

class Game;

class EarthSoldier: public Units
{
public:
	EarthSoldier(int p, int h, int c, Game* g);
	bool attack();
	bool getAttacked();
	bool isDead();
};
#endif