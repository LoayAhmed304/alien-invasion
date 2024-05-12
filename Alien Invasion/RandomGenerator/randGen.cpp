#include "randGen.h"
#include "../Game/Game.h"
#include <cstdlib>
#include <time.h>

randGen::randGen(int n, int es, int et, int eg, int eh, int as,
    int am, int ad, int probability, int infection, int epl,
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
    inf = infection;
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

bool randGen::canInfect()
{
    return ((rand() % 101) <= inf);
}

bool randGen::generateEarth(Units*& newBorn)
{
    if (Units::getTotalUnits(earthArmy) < 999)
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

bool randGen::generateAlien(Units*& newBorn)
{
    if (Units::getTotalUnits(alienArmy) < 999)
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
bool randGen::generateSaver(Units*& newBorn)
{
    if (Units::getTotalUnits(earthArmy) < 999)
    {
        int p, h, c;
        p = earthPowerLow + (rand() % (earthPowerHigh - earthPowerLow + 1));
        h = earthHealthLow + (rand() % (earthHealthHigh - earthHealthLow + 1));
        c = earthCapLow + (rand() % (earthCapHigh - earthCapLow + 1));

        if (h > 100)
            h = 100;

        int B = 1 + (rand() % 100);

        newBorn = new SaverUnit(p, h, c, game);
        return true;
    }
    return false;
}
bool randGen::addUnits()
{
    Units* newBorn = nullptr;
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
    if (game->getEarthArmy()->inDanger() > 10)
        for (int i = 0; i < N; i++)
        {
            if (generateSaver(newBorn))
                game->getAlliedArmy()->addUnit(newBorn);
            else
                break;
        }
    return true;
}
