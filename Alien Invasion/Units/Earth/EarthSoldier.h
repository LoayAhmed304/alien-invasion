#ifndef	EARTH_SOLDIER_H
#define EARTH_SOLDIER_H
#include "../Unit.h"
class Game;

class EarthSoldier: public Unit
{
public:
	EarthSoldier(int p, int h, int c, Game* g);
	bool attack();
};
#endif