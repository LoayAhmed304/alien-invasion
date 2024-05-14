#ifndef	ALIEND_DRONE_H
#define ALIEND_DRONE_H
#include "../Units.h"
class Game;


class AlienDrone : public Units
{
public:
	AlienDrone(int p, int h, int c, Game* g);
	bool attack();
};
#endif