#pragma once
#include "AlienArmy.h"
class Alien_Soldier : public AlienArmy
{
private:
	int ID;
public:
	Alien_Soldier() {}
	Alien_Soldier(int id)
	{
		ID = id;
	}
	bool Attack();
	bool GetAttacked();
};

bool Alien_Soldier::Attack()
{
}

bool Alien_Soldier::GetAttacked()
{
}