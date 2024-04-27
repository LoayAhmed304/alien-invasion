#include "Units.h"
#include "../Game/Game.h"

int Units::eID = 0;
int Units::aID = 2000;

Units::Units(unitType t, int p, int h, int c, Game* g) {
	type = t;
	if (type < alienSoldier)
		++eID;
	else
		++aID;
	power = p;
	health = h;
	cur_health = h;
	attack_cap = c;
	game = g;
	TimeUML = 0;
	Tj = game->getTimestep();
	Ta = 0;
	Td = 0;
}
bool Units::getAttacked(double dmg)
{
	cout << id;
	cur_health -= dmg / sqrt(cur_health);
	if (cur_health < 0)
	{
		cur_health = 0;
		Td = game->getTimestep();
		Dd = Td - Ta;
		Db = Td - Tj;
	}
	return true;
}
bool Units::isDead()
{
	return (cur_health == 0);
}
unitType Units::getType() const
{
	return type;
}

double Units::getHealth() const
{
	return health;
}

double Units::getCurHealth() const
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

int Units::getTa() const
{
	return Ta;
}

void Units::setTa(int ta)
{
	Ta = ta;
	Df = Ta - Tj;
}

int Units::getID()
{
	return id;
}

int Units::getHealthPerc() const
{
	return ((cur_health * 100) / health);
}

int Units::getUMLtime()
{
	return TimeUML;
}

bool Units::exitUML()
{
	TimeUML = 0;
	return true;
}
bool Units::enterUML()
{
	TimeUML = game->getTimestep();
	return true;
}
std::ostream& operator<<(std::ostream& os, const Units* obj)
{
	os << obj->id;
	return os;
}