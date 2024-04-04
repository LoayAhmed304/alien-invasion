#pragma once
class EarthSoldier : public Units
{

public:
	EarthSoldier(int p, int h, int c, int timestep):Units("ES",p, h, c, timestep) {
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