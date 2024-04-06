#ifndef	EARTH_GUNNERY_H
#define EARTH_GUNNERY_H

class EarthGunnery: public Units
{

public:
	EarthGunnery(int p, int h, int c, int timestep): Units("EG", p, h, c, timestep) {
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