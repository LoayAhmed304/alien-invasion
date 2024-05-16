#ifndef	ALIEN_DRONE_H
#define ALIEN_DRONE_H
#include "../Unit.h"
class Game;


class AlienDrone : public Unit
{
public:
	AlienDrone(int p, int h, int c, Game* g);
	bool attack();
};
#endif