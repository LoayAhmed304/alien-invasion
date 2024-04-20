#include "Units.h"
#include "../Game.h"

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
	InsideUML = false;
	TimeUML = 0;
	Tj = game->getTimestep();
}
bool Units::getAttacked(int dmg)
{
	Units* u = this;
	cur_health -= dmg;
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

int Units::getHealthPerc() const
{
	return ((cur_health * 100) / health);
}

bool Units::checkUML() const
{
	return InsideUML;
}

int Units::getUMLtime()
{
	return TimeUML;
}

bool Units::insideUML()
{
	TimeUML++;
	return true;
}

bool Units::exitUML()
{
	TimeUML = 0;
	InsideUML = false;
	return true;
}
bool Units::enterUML()
{
	InsideUML = true;
	return true;
}
std::ostream& operator<<(std::ostream& os, const Units* obj)
{
	os << obj->id;
	return os;
}