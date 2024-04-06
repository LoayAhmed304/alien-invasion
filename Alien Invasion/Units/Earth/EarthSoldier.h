#ifndef	EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

class EarthSoldier: public Units
{

public:
	EarthSoldier(int p, int h, int c, int timestep):Units("ES",p, h, c, timestep) {
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