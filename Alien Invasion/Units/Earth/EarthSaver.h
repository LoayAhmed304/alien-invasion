#ifndef	EARTH_SAVER_H
#define EARTH_SAVER_H
#include "../Units.h"

#include "../Units.h"

class Game;

class EarthSaver : public Units
{
public:
	EarthSaver(int p, int h, int c, Game* g);
	bool attack();
};
#endif