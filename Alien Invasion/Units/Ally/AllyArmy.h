#ifndef ALLY_ARMY_H
#define ALLY_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"


class AllyArmy
{
private:
    LinkedQueue <Units*> SU;
public:
    bool addUnit(Units*);
    bool peekUnit(unitType, Units*&);
    bool getUnit(unitType, Units*&);
    int getLength(unitType);
    bool isEmpty(unitType);
    void print();
    bool fight();        // Peeks each earth unit and calls its attack
    ~AllyArmy();
};
#endif
