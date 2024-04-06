#ifndef	ALIEND_DRONE_H
#define ALIEND_DRONE_H

class AlienDrone : public Units
{

public:
	AlienDrone(int p, int h, int c, int timestep) : Units("AD", p, h, c, timestep) {
		id = aID;
	}

	bool Attack() {
		return true;
	}

	bool GetAttacked() {
		return true;
	}

	bool IsDead() {
		return true;
	}
};
#endif