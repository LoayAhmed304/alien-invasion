#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H
#include "../Unit.h"
class Game;

class AlienMonster : public Unit
{
public:
	AlienMonster(int p, int h, int c, Game*);
	bool attack();
};

#endif