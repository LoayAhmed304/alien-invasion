#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H
#include "../Unit.h"
class Game;

class AlienSoldier : public Unit
{
public:
	AlienSoldier(int p, int h, int c, Game* g);
	bool attack();
};

#endif