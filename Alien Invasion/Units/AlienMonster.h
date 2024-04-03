#pragma once
#include "AlienArmy.h"
class AlienMonster : public Units
{
private:
	int ID;
public:
	AlienMonster() {}
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