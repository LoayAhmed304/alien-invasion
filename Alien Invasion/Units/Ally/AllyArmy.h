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
    bool peekUnit(unitType, Units*&) const;
    bool getUnit(unitType, Units*&);
    int getLength(unitType) const;
    bool isEmpty(unitType) const;
    void print() const;
    bool fight();        // Peeks each ally unit and calls its attack
    ~AllyArmy();
};
#endif