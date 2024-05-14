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
    ArrayStack <Units*> EH;
    int infCount;
    int totalInfected;
public:
    EarthArmy();
    bool addUnit(Units*);
    bool peekUnit(unitType, Units*&) const;
    bool getUnit(unitType, Units*&);
    int getLength(unitType) const;
    bool isEmpty(unitType) const;
    void print() const;
    bool fight();        // Peeks each earth unit and calls its attack
    bool inDanger(int) const;
    bool getRandomES(Units*&, int);

    void incInfected();
    void decInfected();
    int getinfCount() const;
    int getTotalInfected() const;

    ~EarthArmy();
};
#endif
