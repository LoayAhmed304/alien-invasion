#ifndef ALLY_ARMY_H
#define ALLY_ARMY_H

#include "../Unit.h"
#include "../../DataStructures/LinkedQueue.h"

class AllyArmy
{
private:
    LinkedQueue <Unit*> SU;

public:
    bool addUnit(Unit*);
    bool peekUnit(unitType, Unit*&) const;
    bool getUnit(unitType, Unit*&);
    int getLength(unitType) const;
    bool isEmpty(unitType) const;
    void print() const;
    bool fight();        // Peeks each ally unit and calls its attack
    ~AllyArmy();
};
#endif