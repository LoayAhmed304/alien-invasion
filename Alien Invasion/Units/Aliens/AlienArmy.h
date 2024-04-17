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
    bool swapAdd = true;
    bool swapRemove = true;
    bool swapPeek = true;
public:
    bool addUnit(Units*);

    bool peekUnit(unitType, Units*&, int = 0);

    bool getUnit(unitType, Units*&, int = 0);

    bool isEmpty(unitType);

    void print();

    int length(unitType);


    bool fight();        // Peeks each earth unit and calls its attack
};

#endif