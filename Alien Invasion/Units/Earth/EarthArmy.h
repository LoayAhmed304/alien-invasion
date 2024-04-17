#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/ArrayStack.h"
#include "../../DataStructures/priQueue.h"

class EarthArmy
{
private:
    LinkedQueue <Units*> ES;
    ArrayStack <Units*> ET;
    priQueue <Units*> EG;
public:
    bool AddUnit(Units* X);
    bool peekUnit(unitType type, Units*& unit);
    bool getUnit(unitType type, Units*& unit);
    bool isEmpty(unitType type);
    void print();
    bool fight();        // Peeks each earth unit and calls its attack
};
#endif
