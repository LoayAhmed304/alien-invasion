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
        if (!isEmptyAM())
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
        if (!isEmptyAM())
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

    bool isEmptyAS()
    {
        return AS.isEmpty();
    }

    bool isEmptyAM()
    {
        return !AMcount;
    }

    bool isEmptyAD()
    {
        return AD.isEmpty();
    }

    bool isEmpty()
    {
        return (isEmptyAS() && isEmptyAM() && isEmptyAD());
    }

    int lengthAS()
    {
        return AS.length();
    }

    int lengthAM()
    {
        return AMcount;
    }

    int lengthAD()
    {
        return AD.length();
    }

    void printAS()
    {
        cout << AS.length() << " AS [";
        AS.printAll();
        cout << "]\n";
    }

    void printAM()
    {
        cout << AMcount << " AM [";
        if(!isEmptyAM())
        {
            cout << AM[0];
            for (int i = 1; i < AMcount; i++)
            {
                cout << ", " << AM[i];
            }
        }
        cout << "]\n";
    }

    void printAD()
    {
        cout << AD.length() << " AD [";
        AD.printAll();
        cout << "]\n";
    }

    void print()
    {
        printAS();
        printAM();
        printAD();
    }
};

#endif