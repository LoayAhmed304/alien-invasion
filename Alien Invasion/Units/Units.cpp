#include "Units.h"

int Units::eID = 0;
int Units::aID = 0;

Units::Units(string t, int h, int p, int c, int timestep) {
	type = t;
	if(type[0] == 'E')
		eID++;
	else
		aID++;
	Power = p;
	health = h;
	attack_cap = c;
	Tj = timestep;
}