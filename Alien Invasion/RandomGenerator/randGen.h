#ifndef RANDOM_H
#define RANDOM_H

#include "../Units/Aliens/AlienMonster.h"
#include "../Units/Aliens/AlienDrone.h"
#include "../Units/Aliens/AlienSoldier.h"
#include "../Units/Earth/EarthSoldier.h"
#include "../Units/Earth/EarthGunnery.h"
#include "../Units/Earth/EarthTank.h"
#include "../Units/Earth/EarthHeal.h"
#include "../Units/Ally/SaverUnit.h"
class Game;

class randGen
{
private:
	int N, NS, ES, ET, EG, EH, AS, AM, AD, prob, inf, infThreshold,
		earthPowerLow, earthPowerHigh,
		earthHealthLow, earthHealthHigh,
		earthCapLow, earthCapHigh,
		alienPowerLow, alienPowerHigh,
		alienHealthLow, alienHealthHigh,
		alienCapLow, alienCapHigh,
		saverPowerLow, saverPowerHigh,
		saverHealthLow, saverHealthHigh,
		saverCapLow, saverCapHigh;
	Game* game;
public:
	randGen(int n, int ns, int es, int et, int eg, int eh,
		int as, int am, int ad, int probability, int infection, int infthreshold,
		int epl, int eph, int ehl, int ehh, int ecl, int ech,
		int apl, int aph, int ahl, int ahh, int acl, int ach, int spl, int sph, int shl, int shh, int scl, int sch, Game* g);
	bool probability() const;
	bool canInfect() const;
	bool canSpread() const;
	bool generateEarth(Unit*&);
	bool generateAlien(Unit*&);
	bool generateSaver(Unit*&);
	int generateIndex(int) const;
	bool addUnits();
};
#endif
