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
        switch (X->getType()[1])
        {
        case 'S':
            AS.enqueue(X);
            break;
        case 'M':
            AM[AMcount++] = X;
            break;
        case 'D':
            swapAdd = !swapAdd;
            if (swapAdd)
                AD.enqueue(X);
            else
                AD.enqueueFront(X);
            break;
        }
        return true;
    }

    bool peekSoldier(Units*& unit)
    {
        return (AS.peek(unit));
    }

    bool peekMonster(int m, Units*& unit)
    {
        if (!isEmpty('M'))
        {
            unit = AM[m];
            return true;
        }
        return false;
    }

    bool peekDrone(Units*& unit)
    {
        swapPeek = !swapPeek;
        if (swapPeek)
            return (AD.peekRear(unit));
        return (AD.peek(unit));
    }

    bool removeSoldier(Units*& unit)
    {
        return (AS.dequeue(unit));
    }

    bool removeMonster(int m, Units*& unit)
    {
        if (!isEmpty('M'))
        {
            unit = AM[m];
            AM[m] = AM[--AMcount];
            AM[AMcount] = nullptr;
            return true;
        }
        return false;
    }

    bool removeDrone(Units*& unit)
    {
        swapRemove = !swapRemove;
        if (swapRemove)
            return AD.dequeueRear(unit);
        return AD.dequeue(unit);
    }

    bool isEmpty(char s = 'A')
    {
        switch (s) {
        case 'S':
            return AS.isEmpty();
        case 'M':
            return !AMcount;
        case 'D':
            return AD.isEmpty();
        case 'A':
            return (AS.isEmpty() && !AMcount && AD.isEmpty());
        }
    }

    int length(char e)
    {
        switch (e) {
        case 'S':
            return AS.length();
        case 'M':
            return AMcount;
        case 'D':
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
        if (!isEmpty('M'))
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