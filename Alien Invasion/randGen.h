#ifndef RANDOM_H
#define RANDOM_H

#include "Units/Units.h"
#include "Units/Aliens/AlienMonster.h"
#include "Units/Aliens/AlienDrone.h"
#include "Units/Aliens/AlienSoldier.h"
#include "Units/Earth/EarthSoldier.h"
#include "Units/Earth/EarthGunnery.h"
#include "Units/Earth/EarthTanks.h"

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
	int getMonsterIndex(int val);
	Units* generateEarth(int timeStep);
	Units* generateAlien(int timeStep);
	int generateNum(); // for phase 1.2 simulation
	~randGen();
};

#endif