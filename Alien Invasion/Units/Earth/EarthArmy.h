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
    ///////////
    ArrayStack <Units*> EH;
    ///////////////////////////////////////////////////////////////////
    LinkedQueue <Units*> SU;

    bool inDanger = false;
    int countinf = 0;
public:
    bool addUnit(Units*);
    bool peekUnit(unitType, Units*&);
    bool getUnit(unitType, Units*&);
    int getLength(unitType);
    bool isEmpty(unitType);
    void print();
    bool fight();        // Peeks each earth unit and calls its attack
    bool countInfected();
    int percInfected();
    int getInfectedCount();
    ~EarthArmy();
};
#endif
