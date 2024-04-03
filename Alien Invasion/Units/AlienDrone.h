#pragma once
#include "AlienArmy.h"
class AlienDrone : public Units
{
private:
	int ID;
public:
	AlienDrone() {}
	bool SetID(int id)
	{
		ID = id;
		return true;
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