#ifndef RANDOM_H
#define RANDOM_H

#include "../Units/Units.h"
#include "../Units/Aliens/AlienMonster.h"
#include "../Units/Aliens/AlienDrone.h"
#include "../Units/Aliens/AlienSoldier.h"
#include "../Units/Earth/EarthSoldier.h"
#include "../Units/Earth/EarthGunnery.h"
#include "../Units/Earth/EarthTank.h"
#include "../Units/Earth/EarthHeal.h"
#include "../Units/Earth/EarthSaver.h"

class Game;

class randGen
{
private:
	int N, ES, ET, EG, EH, AS, AM, AD, prob,
		earthPowerLow, earthPowerHigh,
		earthHealthLow, earthHealthHigh,
		earthCapLow, earthCapHigh,
		alienPowerLow, alienPowerHigh,
		alienHealthLow, alienHealthHigh,
		alienCapLow, alienCapHigh,
		saverPower, saverHealth, saverCap,
		infPerc;
	Game* game;
public:
	randGen(int n, int es, int et, int eg, int eh,
		int as, int am, int ad, int probability,
		int epl, int eph, int ehl, int ehh, int ecl, int ech,
		int apl, int aph, int ahl, int ahh, int acl, int ach, int sp, int sh, int sc, int inf, Game* g);
	bool probability();
	Units* generateEarth();
	Units* generateAlien();
	bool addUnits();
};
#endif
