#ifndef ALLIED_ARMY_H
#define ALLIED_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"


class AlliedArmy
{
private:
    LinkedQueue <Units*> SU;
public:
    bool addUnit(Units*);
    bool peekUnit(unitType, Units*&);
    bool getUnit(unitType, Units*&);
    int getLength(unitType);
    bool isEmpty();
    void print();
    bool fight();        // Peeks each earth unit and calls its attack
    ~AlliedArmy();
};
#endif
