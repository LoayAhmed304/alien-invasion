#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/Deque.h"

class AlienArmy{
private:
    LinkedQueue<Units*> AS;
    Units* AM[1000];
    int AMcount = 0;
    Deque<Units*> AD;
    bool swapAdd = true;
    bool swapRemove = true;
    bool swapPeek = true;
public:
    bool addUnit(Units* X);

    bool peekUnit(unitType, Units*&, int = 0);

    bool getUnit(unitType, Units*&, int = 0);

    bool isEmpty(unitType);

    void print();

    bool fight();        // Peeks each earth unit and calls its attack
};

#endif