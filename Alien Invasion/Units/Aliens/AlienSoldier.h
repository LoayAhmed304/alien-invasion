#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

class AlienSoldier : public Units
{

public:
	AlienSoldier(int p, int h, int c, int timestep) : Units("AS", p, h, c, timestep) {
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