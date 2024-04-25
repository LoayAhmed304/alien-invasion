#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/Deque.h"
#include "../../DataStructures/RandomArray.h"
#include <string>

class AlienArmy{
private:
    LinkedQueue<Units*> AS;
    RandomArray<Units*> AM;
    Deque<Units*> AD;
    bool swap = true;
    bool swapPeek = true;

public:
    bool addUnit(Units*);
    bool peekUnit(unitType, Units*&, int = 0);
    bool getUnit(unitType, Units*&, int = 0);
    int getLength(unitType);
    bool isEmpty(unitType);
    void print();
    bool fight(int m = 0);        // Peeks each earth unit and calls its attack
    ~AlienArmy();
};

#endif
