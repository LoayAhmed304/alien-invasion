#ifndef	EARTH_TANK_H
#define EARTH_TANK_H

class EarthTank : public Units
{

public:
	EarthTank(int p, int h, int c, int timestep) : Units("ET", p, h, c, timestep) {
		id = eID;
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