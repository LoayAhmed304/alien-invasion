#include "Units.h"

int Units::eID = 0;
int Units::aID = 2000;

Units::Units(unitType t, int h, int p, int c, int timestep) {
	type = t;
	if(type < 3)
		++eID;
	else
		++aID;
	power = p;
	health = h;
	cur_health = h;
	attack_cap = c;
	Tj = timestep;
}
bool Units::GetAttacked(int dmg)
{
	cur_health -= dmg; // to be (dmg / sqrt(cur-health)) in phase 2
	return true;
}
unitType Units::getType() const
{
	return type;
}

int Units::getHealth() const
{
	return health;
}

int Units::getCurHealth() const
{
	return cur_health;
}

int Units::getPower() const
{
	return power;
}

int Units::getAttackCap() const
{
	return attack_cap;
}

void Units::setGame(Game* g)
{
	game = g;
}

std::ostream& operator<<(std::ostream& os, const Units* obj)
{
	os << obj->id;
	return os;
}
