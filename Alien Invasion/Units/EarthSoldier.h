#pragma once
#include "EarthArmy.h"
class EarthSoldier : public Units
{
private:
	int ID;
public:
	EarthSoldier() {}
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