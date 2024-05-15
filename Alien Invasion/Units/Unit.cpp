#include "Unit.h"
#include "../Game/Game.h"

int Unit::eID = 0;
int Unit::aID = 2000;
int Unit::sID = 4000;

Unit::Unit(unitType t, int p, int h, int c, Game* g) : Ta(0), Td(0), timeUML(0), Db(0), Dd(0), Df(0), UAP(0), id(0), healed(false), infected(false), cured(false), HT(0)

{
	type = t;
	if (type < alienSoldier)
		++eID;
	else if (type < alienArmy)
		++aID;
	else
		++sID;
	power = p;
	health = h;
	cur_health = h;
	attack_cap = c;
	game = g;
	Tj = game->getTimestep();
}

bool Unit::getAttacked(double dmg)
{
	cur_health -= dmg;

	if (cur_health <= 0)
	{
		cur_health = 0;
		Td = game->getTimestep();
		Dd = Td - Ta;
		Db = Td - Tj;
	}

	return true;
}
bool Unit::isDead() const
{
	return cur_health == 0;
}

unitType Unit::getType() const
{
	return type;
}

double Unit::getHealth() const
{
	return health;
}

double Unit::getCurHealth() const
{
	return cur_health;
}

int Unit::getPower() const
{
	return power;
}

int Unit::getAttackCap() const
{
	return attack_cap;
}

int Unit::getTa() const
{
	return Ta;
}

void Unit::setTa(int ta)
{
	Ta = ta;
	Df = Ta - Tj;
}

int Unit::getTotalUnits(unitType t)
{
	switch (t)
	{
	case earthArmy:
		return eID;
	case alienArmy:
		return aID - 2000;
	}
}

int Unit::getTd() const
{
	return Td;
}

int Unit::getID() const
{
	return id;
}

int Unit::getTj() const
{
	return Tj;
}

int Unit::getDf() const
{
	return Df;
}

int Unit::getDd() const
{
	return Dd;
}

int Unit::getDb() const
{
	return Db;
}

int Unit::getHealthPerc() const
{
	return ((cur_health * 100) / health);
}

bool Unit::isHealed() const
{
	return healed;
}

void Unit::heal()
{
	healed = true;
	game->getEarthArmy()->updateHealed();
}

int Unit::getUMLtime() const
{
	return timeUML;
}

bool Unit::exitUML()
{
	timeUML = 0;
	return true;
}

bool Unit::enterUML()
{
	timeUML = game->getTimestep();
	if (!infected)
		HT = 0;
	return true;
}

bool Unit::isInfected() const
{
	return infected;
}

bool Unit::isCured() const
{
	return cured;
}

bool Unit::getInfected()
{
	if (!cured)
	{
		infected = true;
		game->getEarthArmy()->incInfected();
		return true;
	}
	return false;
}

void Unit::removeInfected()
{
	infected = false;
}

void Unit::getCured()
{
	cured = true;
	game->getEarthArmy()->decInfected();
}

int Unit::getHT() const
{
	return HT;
}

void Unit::setHT(int a)
{
	HT = a;
}

void Unit::incHT()
{
	++HT;
}

void Unit::setUAP(double dmg)
{
	UAP = dmg;
}

double Unit::getUAP() const
{
	return UAP;
}

std::ostream& operator<<(std::ostream& os, const Unit* obj)
{
	string color = "";
	if (obj->getType() < alienSoldier)
		color = "\033[1;34m";
	else if (obj->getType() == saverUnit)
		color = "\033[1;33m";
	else
		color = "\033[1;32m";
	if (obj->infected)
		os << "\033[1;32m$\033[1;34m";
	os << color << obj->id << "\033[0m";

	return os;
}

string operator+(const string& lhs, const Unit* obj)
{
	string s = "";
	string x = "";
	if (obj->getType() < alienSoldier)
		s = "\033[1;34m";
	else if (obj->getType() == saverUnit)
		s = "\033[1;33m";
	else
		s = "\033[1;32m";
	if (obj->infected)
		x += "\033[1;32m$\033[1;34m";
	return lhs + x + s + to_string(obj->getID()) + "\033[0m";
}
