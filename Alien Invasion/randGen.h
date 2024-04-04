#ifndef RANDOM_H
#define RANDOM_H

#include "Units/Units.h"
#include "Units/AlienMonster.h"
#include "Units/AlienDrone.h"
#include "Units/AlienSoldier.h"
#include "Units/EarthSoldier.h"
#include "Units/EarthGunners.h"
#include "Units/EarthTanks.h"

class randGen
{
private:
	int N, ES, ET, EG, AS, AM, AD, prob,
		earthPowerLow, earthPowerHigh,
		earthHealthLow, earthHealthHigh,
		earthCapLow, earthCapHigh,
		alienPowerLow, alienPowerHigh,
		alienHealthLow, alienHealthHigh,
		alienCapLow, alienCapHigh;
public:
	randGen(int n, int es, int et, int eg,
		int as, int am, int ad, int probability,
		int epl, int eph, int ehl, int ehh, int ecl, int ech,
		int apl, int aph, int ahl, int ahh, int acl, int ach);
	bool probability(int&);
	Units* generateEarth(int timeStep);
	Units* generateAlien(int timeStep);
	~randGen();
};

#endif