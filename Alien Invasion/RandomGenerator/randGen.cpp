#include "randGen.h"
#include "../Game/Game.h"
#include <cstdlib>
#include <time.h>

randGen::randGen(int n, int ns, int es, int et, int eg, int eh, int as,
    int am, int ad, int probability, int infection, int infthreshold, 
    int epl, int eph, int ehl, int ehh, int ecl, int ech,
    int apl, int aph, int ahl, int ahh, int acl, int ach, int spl, int sph, int shl, int shh, int scl, int sch, Game* g)
{
    srand(time(0));

    N = n;
    NS = ns;
    ES = es;
    ET = et;
    EG = eg;
    EH = eh;
    AS = as;
    AM = am;
    AD = ad;
    prob = probability;
    inf = infection;
    infThreshold = infthreshold;
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
    saverPowerLow = spl;
    saverPowerHigh = sph;
    saverHealthLow = shl;
    saverHealthHigh = shh;
    saverCapLow = scl;
    saverCapHigh = sch;
    game = g;
}

bool randGen::probability() const
{
    return ((rand() % 101) <= prob);
}

bool randGen::canInfect() const
{
    return ((rand() % 101) <= inf);
}

bool randGen::canSpread() const
{
    return ((rand() % 101) <= 2);
}

bool randGen::generateEarth(Unit*& newBorn)
{
    if (Unit::getTotalUnits(earthArmy) < 999)
    {
        int p, h, c;
        p = earthPowerLow + (rand() % (earthPowerHigh - earthPowerLow + 1));
        h = earthHealthLow + (rand() % (earthHealthHigh - earthHealthLow + 1));
        c = earthCapLow + (rand() % (earthCapHigh - earthCapLow + 1));

        if (h > 100)
            h = 100;

        int B = 1 + (rand() % 100);
        if (B < ES)
            newBorn = new EarthSoldier(p, h, c, game);
        else if (B < ES + ET)
            newBorn = new EarthTank(p, h, c, game);
        else if (B < ES + ET + EG)
            newBorn = new EarthGunnery(p, h, c, game);
        else
            newBorn = new EarthHeal(p, h, c, game);
        return true;
    }

    return false;
}

bool randGen::generateAlien(Unit*& newBorn)
{
    if (Unit::getTotalUnits(alienArmy) < 999)
    {
        int p, h, c;
        p = alienPowerLow + (rand() % (alienPowerHigh - alienPowerLow + 1));
        h = alienHealthLow + (rand() % (alienHealthHigh - alienHealthLow + 1));
        c = alienCapLow + (rand() % (alienCapHigh - alienCapLow + 1));

        if (h > 100)
            h = 100;

        int B = 1 + (rand() % 100);
        if (B < AS)
            newBorn = new AlienSoldier(p, h, c, game);
        else if (B < AS + AM)
            newBorn = new AlienMonster(p, h, c, game);
        else
            newBorn = new AlienDrone(p, h, c, game);

        return true;
    }
    return false;
}
bool randGen::generateSaver(Unit*& newBorn)
{
    int p, h, c;
    p = saverPowerLow + (rand() % (saverPowerHigh - saverPowerLow + 1));
    h = saverHealthLow + (rand() % (saverHealthHigh - saverHealthLow + 1));
    c = saverCapLow + (rand() % (saverCapHigh - saverCapLow + 1));

    if (h > 100)
        h = 100;

    int B = 1 + (rand() % 100);

    newBorn = new SaverUnit(p, h, c, game);

    return true;
}

int randGen::generateIndex(int size) const
{
    return (rand() % size);
}

bool randGen::addUnits()
{
    Unit* newBorn = nullptr;
    if (game->getEarthArmy()->inDanger(infThreshold))
        for (int i = 0; i < NS; i++)
        {
            generateSaver(newBorn);
            game->getAllyArmy()->addUnit(newBorn);
        }
    if (probability())
        for (int i = 0; i < N; i++)
        {
            if (generateEarth(newBorn))
                game->getEarthArmy()->addUnit(newBorn);
            else
                break;
        }
    if (probability())
        for (int i = 0; i < N; i++)
        {
            if(generateAlien(newBorn))
                game->getAlienArmy()->addUnit(newBorn);
            else
                break;
        }

    return true;
}