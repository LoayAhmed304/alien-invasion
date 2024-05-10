#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H
#include "../Units.h"
#include "../Earth/EarthSoldier.h"

class Game;

class AlienMonster : public Units
{
public:
	AlienMonster(int p, int h, int c, Game*);
	bool attack();
	bool infect(Units* enemy);
};

#endif