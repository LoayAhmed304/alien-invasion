#ifndef	EARTH_TANK_H
#define EARTH_TANK_H
#include "../Unit.h"
class Game;

class EarthTank : public Unit
{
public:
	EarthTank(int p, int h, int c, Game* g);
	bool attack();
};
#endif