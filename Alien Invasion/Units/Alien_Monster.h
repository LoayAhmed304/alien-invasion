#pragma once
#include "AlienArmy.h"
class Alien_Monster : public AlienArmy
{
private:
	int ID;
public:
	Alien_Monster() {}
	Alien_Monster(int id)
	{
		ID = id;
	}
	bool Attack();
	bool GetAttacked();
};

bool Alien_Monster::Attack()
{
}

bool Alien_Monster::GetAttacked()
{
}