#pragma once
#include "AlienArmy.h"
class Alien_Drone : public AlienArmy
{
private:
	int ID;
public:
	Alien_Drone() {}
	Alien_Drone(int id)
	{
		ID = id;
	}
	bool Attack() {};
	bool GetAttacked() {};
};