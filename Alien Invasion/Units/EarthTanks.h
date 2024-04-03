#pragma once
#include "EarthArmy.h"
class EarthTanks : public Units
{
private:
	int ID;
public:
	EarthTanks() {}
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