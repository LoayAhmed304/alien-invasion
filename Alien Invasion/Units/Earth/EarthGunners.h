#pragma once
class EarthGunners :public Units
{

public:
	EarthGunners(int p, int h, int c, int timestep) : Units("EG", p, h, c, timestep) {
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