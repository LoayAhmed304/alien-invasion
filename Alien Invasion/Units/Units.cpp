#include "Units.h"

int Units::eID = 0;
int Units::aID = 2000;

Units::Units(string t, int h, int p, int c, int timestep) {
	type = t;
	if(type[0] == 'E')
		eID++;
	else
		aID++;
	Power = p;
	health = h;
	cur_health = health;
	attack_cap = c;
	Tj = timestep;
}
string Units::getType() const
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
	return Power;
}

int Units::getAttackCap() const
{
	return attack_cap;
}