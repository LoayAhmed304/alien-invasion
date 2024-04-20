#include "randGen.h"
#include "Game.h"
#include <cstdlib>
#include <time.h>

randGen::randGen(int n, int es, int et, int eg, int eh, int as,
    int am, int ad, int probability, int epl,
    int eph, int ehl, int ehh, int ecl, int ech,
    int apl, int aph, int ahl, int ahh, int acl, int ach, Game* g)
{
    srand(time(0));

    N = n;
    ES = es;
    ET = et;
    EG = eg;
    EH = eh;
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
    game = g;
}

bool randGen::probability()
{
    return ((rand() % 101) <= prob);
}

int randGen::getMonsterIndex(int val)
{
    return (rand() % val);
}

Units* randGen::generateEarth()
{
    int p, h, c;
    p = earthPowerLow + (rand() % (earthPowerHigh - earthPowerLow + 1));
    h = earthHealthLow + (rand() % (earthHealthHigh - earthHealthLow + 1));
    c = earthCapLow + (rand() % (earthCapHigh - earthCapLow + 1));

    Units* newBorn;
    int B = 1 + (rand() % 100);
    if (B < ES)
        newBorn = new EarthSoldier(p, h, c, game);
    else if (B < ES + ET)
        newBorn = new EarthTank(p, h, c, game);
    else if (B < ES + ET + EG)
        newBorn = new EarthGunnery(p, h, c, game);
    else
        newBorn = new EarthHeal(p, h, c, game);
    return newBorn;
}

Units* randGen::generateAlien()
{
    int p, h, c;
    p = alienPowerLow + (rand() % (alienPowerHigh - alienPowerLow + 1));
    h = alienHealthLow + (rand() % (alienHealthHigh - alienHealthLow + 1));
    c = alienCapLow + (rand() % (alienCapHigh - alienCapLow + 1));

    Units* newBorn;
    int B = 1 + (rand() % 100);
    if (B < AS)
        newBorn = new AlienSoldier(p, h, c, game);
    else if (B < AS + AM)
        newBorn = new AlienMonster(p, h, c, game);
    else
        newBorn = new AlienDrone(p, h, c, game);

    return newBorn;
}
bool randGen::addUnits()
{
    Units* newBorn = nullptr;
    if (probability())
        for (int i = 0; i < N; i++)
        {
            newBorn = generateEarth();
            game->getEarthArmy()->addUnit(newBorn);
        }
    if (probability())
        for (int i = 0; i < N; i++)
        {
            newBorn = generateAlien();
            game->getAlienArmy()->addUnit(newBorn);
        }
    return true;
}
int randGen::generateNum() // for phase 1.2 simulation
{
    return (1 + (rand() % 100));
}
randGen::~randGen() {}