#pragma once
class EarthTanks : public Units
{

public:
	EarthTanks(int p, int h, int c, int timestep) : Units("ET", p, h, c, timestep) {
		id = eID;
	}
	/*bool SetID(int id)
	{
		ID = id;
		return true;
	}*/
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