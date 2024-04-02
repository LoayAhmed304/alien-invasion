#pragma once
#include "EarthArmy.h"
class Earth_Tanks : public Units
{
private:
	int ID;
public:
	Earth_Tanks() {}
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