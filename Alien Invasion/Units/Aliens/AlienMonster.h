#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

class AlienMonster : public Units
{

public:
	AlienMonster(int p, int h, int c, int timestep) : Units(alienMonster, p, h, c, timestep) {
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