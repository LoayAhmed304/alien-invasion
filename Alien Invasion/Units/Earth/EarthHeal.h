#ifndef	EARTH_HEAL_H
#define EARTH_HEAL_H
#include "../Units.h"

class Game;
class EarthHeal : public Units
{
public:
	EarthHeal(int p, int h, int c, Game* g);
	bool attack(string&);
};
#endif