#ifndef	EARTH_HEAL_H
#define EARTH_HEAL_H
#include "../Unit.h"
class Game;

class EarthHeal : public Unit
{
public:
	EarthHeal(int p, int h, int c, Game* g);
	bool attack();
};
#endif