#pragma once
#include "EarthArmy.h"
class Earth_Gunners :public Units
{
private:
	int ID;
public:
	Earth_Gunners() {}
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