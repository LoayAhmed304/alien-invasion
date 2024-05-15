#ifndef	EARTH_GUNNERY_H
#define EARTH_GUNNERY_H
#include "../Unit.h"
class Game;

class EarthGunnery: public Unit
{
public:
	EarthGunnery(int p, int h, int c, Game* g);
	bool attack();
};
#endif