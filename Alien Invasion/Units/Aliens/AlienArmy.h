#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/Deque.h"
#include "../../DataStructures/RandomArray.h"

class AlienArmy{
private:
    LinkedQueue<Units*> AS;
    RandomArray<Units*> AM;
    Deque<Units*> AD;
    float totalDf, totalDd, totalDb;    // Total D(f,d,b) for the destructed units
    bool swap;
    bool swapPeek;

public:
    AlienArmy();
    bool addUnit(Units*);
    bool peekUnit(unitType, Units*&);
    bool getUnit(unitType, Units*&);
    int getLength(unitType);
    bool isEmpty(unitType) const;
    void print() const;
    bool fight();        // Peeks each earth unit and calls its attack

    void updateD(Units*);
    void returnD(float&, float&, float&) const;
    ~AlienArmy();
};

#endif
