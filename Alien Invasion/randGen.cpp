#include "randGen.h"
#include <cstdlib>
#include <time.h>

randGen::randGen(int n, int es, int et, int eg, int as,
                int am, int ad, int probability, int epl,
                int eph,int ehl, int ehh, int ecl, int ech,
                int apl,int aph, int ahl, int ahh, int acl, int ach)
{
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

bool randGen::probability()
{
    srand(time(0));
    return (1 + (rand() % 100) <= prob);
}

unit* randGen::generateEarth(int timeStep)
{
    srand(time(0));

    int p, h, c;
    p = earthPowerLow + (rand() % (earthPowerHigh - earthPowerLow + 1));
    h = earthHealthLow + (rand() % (earthHealthHigh - earthHealthLow + 1));
    c = earthCapLow + (rand() % (earthCapHigh - earthCapLow + 1));

    unit* newBorn;
    int B = 1 + (rand() % 100);
    if (B < ES)
    {
        newBorn = new earthSoldier(p, h, c, timeStep);
    }
    else if (B < ES + ET)
    {
        newBorn = new earthTank(p, h, c, timeStep);
    }
    else
    {
        newBorn = new earthGunnery(p, h, c, timeStep);
    }

    return newBorn;
}

unit* randGen::generateAlien(int timeStep)
{
    srand(time(0));

    int p, h, c;
    p = alienPowerLow + (rand() % (alienPowerHigh - alienPowerLow + 1));
    h = alienHealthLow + (rand() % (alienHealthHigh - alienHealthLow + 1));
    c = alienCapLow + (rand() % (alienCapHigh - alienCapLow + 1));

    unit* newBorn;
    int B = 1 + (rand() % 100);
    if (B < AS)
    {
        newBorn = new alienSoldier(p, h, c, timeStep);
    }
    else if (B < AS + AM)
    {
        newBorn = new alienMonster(p, h, c, timeStep);
    }
    else
    {
        newBorn = new alienDrone(p, h, c, timeStep);
    }

    return newBorn;
}

randGen::~randGen() {}
