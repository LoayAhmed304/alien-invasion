#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../Unit.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/Deque.h"
#include "../../DataStructures/RandomArray.h"

class AlienArmy{
private:
    LinkedQueue<Unit*> AS;
    RandomArray<Unit*> AM;
    Deque<Unit*> AD;
    float totalDf, totalDd, totalDb;    // Total D(f/d/b) for the destructed units (float for the decimal represntation in output file creation)
    bool swap;
    bool swapPeek;

public:
    AlienArmy();
    bool addUnit(Unit*);
    bool peekUnit(unitType, Unit*&);
    bool getUnit(unitType, Unit*&);
    int getLength(unitType);
    bool isEmpty(unitType) const;
    void print() const;
    bool fight();        // Peeks each earth unit and calls its attack

    void updateD(Unit*);
    void returnD(float&, float&, float&) const;
    ~AlienArmy();
};

#endif
