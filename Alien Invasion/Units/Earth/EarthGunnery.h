#ifndef	EARTH_GUNNERY_H
#define EARTH_GUNNERY_H
#include "../Units.h"
class Game;

class EarthGunnery: public Units
{
public:
	EarthGunnery(int p, int h, int c, Game* g);
	bool attack();
};
#endif