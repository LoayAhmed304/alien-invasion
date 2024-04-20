#ifndef	EARTH_TANK_H
#define EARTH_TANK_H
#include "../Units.h"

#include "../Units.h"

class Game;

class EarthTank : public Units
{
public:
	EarthTank(int p, int h, int c, Game* g);
	bool attack();
	bool getAttacked();
};
#endif