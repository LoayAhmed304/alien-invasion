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
    bool addUnit(Units* X)
    {
        switch (X->getType())
        {
        case alienSoldier:
            AS.enqueue(X);
            break;
        case alienMonster:
            AM[AMcount++] = X;
            break;
        case alienDrone:
            swapAdd = !swapAdd;
            if (swapAdd)
                AD.enqueue(X);
            else
                AD.enqueueFront(X);
            break;
        }
        return true;
    }

    bool peekUnit(unitType type, Units*& unit, int m = 0)
    {
        int n;
        switch (type) {
        case alienSoldier:
            return (AS.peek(unit));
        case alienMonster:
            if (!isEmpty(alienMonster))
            {
                unit = AM[m];
                return true;
            }
            return false;
        case alienDrone:
            swapPeek = !swapPeek;
            if (swapPeek)
                return (AD.peekRear(unit));
            return (AD.peek(unit));
        }
    }

    bool getUnit(unitType type, Units*& unit, int m = 0)
    {
        switch (type) {
        case alienSoldier:
            return (AS.dequeue(unit));
        case alienMonster:
            if (!isEmpty(alienMonster))
            {
                unit = AM[m];
                AM[m] = AM[--AMcount];
                AM[AMcount] = nullptr;
                return true;
            }
            return false;
        case alienDrone:
            swapRemove = !swapRemove;
            if (swapRemove)
                return AD.dequeueRear(unit);
            return AD.dequeue(unit);
        }
    }

    bool isEmpty(unitType type)
    {
        switch (type) {
        case alienSoldier:
            return AS.isEmpty();
        case alienMonster:
            return !AMcount;
        case alienDrone:
            return AD.isEmpty();
        default:
            return (AS.isEmpty() && !AMcount && AD.isEmpty());
        }
    }

    int length(unitType type)
    {
        switch (type) {
        case alienSoldier:
            return AS.length();
        case alienMonster:
            return AMcount;
        case alienDrone:
            return AD.length();
        }
    }

    void print()
    {
        ///     Print all Alien Soldiers
        cout << AS.length() << " AS [";
        AS.printAll();
        cout << "]\n";

        ///     Print all Alien Monsters
        cout << AMcount << " AM [";
        if (!isEmpty(alienMonster))
        {
            cout << AM[0];
            for (int i = 1; i < AMcount; i++)
            {
                cout << ", " << AM[i];
            }
        }
        cout << "]\n";

        ///     Print all Alien Drones
        cout << AD.length() << " AD [";
        AD.printAll();
        cout << "]\n";
    }
};

#endif