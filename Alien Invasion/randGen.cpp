#include "randGen.h"
#include <cstdlib>
#include <time.h>

randGen::randGen(int n, int es, int et, int eg, int as,
                int am, int ad, int probability, int epl,
                int eph,int ehl, int ehh, int ecl, int ech,
                int apl,int aph, int ahl, int ahh, int acl, int ach)
{
    srand(time(0));

    N = n;
    ES = es;
    ET = et;
    EG = eg;
    AS = as;
    AM = am;
    AD = ad;
    prob = probability;
    earthPowerLow = epl;
    earthPowerHigh = eph;
    earthHealthLow = ehl;
    earthHealthHigh = ehh;
    earthCapLow = ecl;
    earthCapHigh = ech;
    alienPowerLow = apl;
    alienPowerHigh = aph;
    alienHealthLow = ahl;
    alienHealthHigh = ahh;
    alienCapLow = acl;
    alienCapHigh = ach;
}

bool randGen::probability(int& n)
{
    n = N;
    return (1 + (rand() % 100) <= prob);
}

int randGen::getMonsterIndex(int val)
{
    return (rand() % val);
}

Units* randGen::generateEarth(int timeStep)
{

    int p, h, c;
    p = earthPowerLow + (rand() % (earthPowerHigh - earthPowerLow + 1));
    h = earthHealthLow + (rand() % (earthHealthHigh - earthHealthLow + 1));
    c = earthCapLow + (rand() % (earthCapHigh - earthCapLow + 1));

    Units* newBorn;
    int B = 1 + (rand() % 100);
    if (B < ES)
    {
        newBorn = new EarthSoldier(p, h, c, timeStep);
    }
    else if (B < ES + ET)
    {
        newBorn = new EarthTanks(p, h, c, timeStep);
    }
    else
    {
        newBorn = new EarthGunnery(p, h, c, timeStep);
    }

    return newBorn;
}

Units* randGen::generateAlien(int timeStep)
{

    int p, h, c;
    p = alienPowerLow + (rand() % (alienPowerHigh - alienPowerLow + 1));
    h = alienHealthLow + (rand() % (alienHealthHigh - alienHealthLow + 1));
    c = alienCapLow + (rand() % (alienCapHigh - alienCapLow + 1));

    Units* newBorn;
    int B = 1 + (rand() % 100);
    if (B < AS)
    {
        newBorn = new AlienSoldier(p, h, c, timeStep);
    }
    else if (B < AS + AM)
    {
        newBorn = new AlienMonster(p, h, c, timeStep);
    }
    else
    {
        newBorn = new AlienDrone(p, h, c, timeStep);
    }

    return newBorn;
}
int randGen::generateNum() // for phase 1.2 simulation
{
    return (1 + (rand() % 100));
}
randGen::~randGen() {}
