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
    bool addUnit(Units*);

    bool peekUnit(unitType, Units*&);

    bool getUnit(unitType, Units*&);

    bool isEmpty(unitType);

    void print();

    bool fight();        // Peeks each earth unit and calls its attack
};
#endif
