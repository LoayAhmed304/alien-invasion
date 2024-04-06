#pragma once
class AlienDrone : public Units
{

public:
	AlienDrone(int p, int h, int c, int timestep) : Units("AD", p, h, c, timestep) {
		id = aID;
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