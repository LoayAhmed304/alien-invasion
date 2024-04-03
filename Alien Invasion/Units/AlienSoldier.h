#pragma once
#include "AlienArmy.h"
class AlienSoldier : public Units
{
private:
	int ID;
public:
	AlienSoldier() {}
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