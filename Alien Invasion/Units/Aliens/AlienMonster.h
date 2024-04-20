#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H
#include "../Units.h"

#include "../Units.h"

class Game;

class AlienMonster : public Units
{
public:
	AlienMonster(int p, int h, int c, Game*);
	bool attack();
	bool getAttacked();
};

#endif