#pragma once
#include "EarthArmy.h"
class EarthGunners :public Units
{
private:
	int ID;
public:
	EarthGunners() {}
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