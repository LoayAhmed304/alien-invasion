#include "Units.h"
#include "../Game/Game.h"

int Units::eID = 0;
int Units::aID = 2000;

Units::Units(unitType t, int p, int h, int c, Game* g) {
	type = t;
	if (type < alienSoldier || type == saverUnit)
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
	cur_health -= dmg / sqrt(cur_health);

	if (cur_health <= 0)
	{
		cur_health = 0;
		Td = game->getTimestep();
		Dd = Td - Ta;
		Db = Td - Tj;
		if (this->getType() < alienSoldier)
		{
			game->updateED(this);
		}
		else
		{
			game->updateAD(this);
		}
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
bool Units::isInfected() const
{
	return infected;
}
bool Units::isCured()
{
	return cured;
}
void Units::getInfected()
{
	if (!cured)
	{
		infected = true;
		game->getEarthArmy()->incInfected();
	}
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
std::ostream& operator<<(std::ostream& os, const Units* obj)
{
	string color = "";
	if (obj->getType() < alienSoldier || obj->getType() == saverUnit)
		color = "\033[1;34m";
	else
		color = "\033[1;32m";
	if (obj->infected)
		os << "$";
	os << color << obj->id << "\033[0m";
	return os;
}