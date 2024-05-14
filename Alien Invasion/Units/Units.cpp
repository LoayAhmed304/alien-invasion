#include "Units.h"
#include "../Game/Game.h"

int Units::eID = 0;
int Units::aID = 2000;
int Units::sID = 4000;

Units::Units(unitType t, int p, int h, int c, Game* g) : Ta(0), Td(0), timeUML(0), Db(0), Dd(0), Df(0), UAP(0), id(0), healed(false), infected(false), cured(false), HT(0), infector(false)
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

bool Units::getAttacked(double dmg)
{
	cur_health -= dmg / sqrt(cur_health);

	if (cur_health <= 0)
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
	return cur_health == 0;
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

int Units::getTotalUnits(unitType t)
{
	switch (t)
	{
	case earthArmy:
		return eID;
	case alienArmy:
		return aID - 2000;
	}
}

int Units::getTd() const
{
	return Td;
}

int Units::getID() const
{
	return id;
}

int Units::getTj() const
{
	return Tj;
}

int Units::getDf() const
{
	return Df;
}

int Units::getDd() const
{
	return Dd;
}

int Units::getDb() const
{
	return Db;
}

int Units::getHealthPerc() const
{
	return ((cur_health * 100) / health);
}

bool Units::isHealed()
{
	return healed;
}

void Units::heal()
{
	healed = true;
	game->updateHealed();
}

int Units::getUMLtime()
{
	return timeUML;
}

bool Units::exitUML()
{
	timeUML = 0;
	return true;
}

bool Units::enterUML()
{
	timeUML = game->getTimestep();
	if (!infected)
		HT = 0;
	return true;
}

bool Units::isInfected() const
{
	return infected;
}

bool Units::isCured()
{
	return cured;
}

bool Units::getInfected()
{
	if (!cured)
	{
		infected = true;
		game->getEarthArmy()->incInfected();
		return true;
	}
	return false;
}

void Units::removeInfected()
{
	infected = false;
}

void Units::getCured()
{
	cured = true;
	game->getEarthArmy()->decInfected();
}

int Units::getHT()
{
	return HT;
}

void Units::setHT(int a)
{
	HT = a;
}

void Units::incHT()
{
	++HT;
}

void Units::setUAP(double dmg)
{
	UAP = dmg;
}

double Units::getUAP()
{
	return UAP;
}

std::ostream& operator<<(std::ostream& os, const Units* obj)
{
	string color = "";
	if (obj->getType() < alienSoldier)
		color = "\033[1;34m";
	else if(obj->getType() == saverUnit)
		color = "\033[1;33m";
	else
		color = "\033[1;32m";
	if (obj->infected)
		os << "\033[1;32m$\033[1;34m";
	os << color << obj->id << "\033[0m";

	return os;
}