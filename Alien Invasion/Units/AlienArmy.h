#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "Units.h"
#include "AlienSoldier.h"
#include "AlienMonster.h"
#include "AlienDrone.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/Deque.h"

class AlienArmy{
private:
    LinkedQueue <Units*> AS;
    Units * AM [10000];
    int AMcount = 0;
    Deque <Units*> AD;
    bool swapAdd = false;
    bool swapRemove = false;
public:
    Units* getSoldier()
    {
        Units* unit;
        AS.peek(unit);
        return unit;
    }

    Units* getMonster(int m)
    {
        Units* unit;
        unit = AM[m];
        return unit;
    }

    Units* getDrone(bool D)
    {
        Units* unit;
        if (D)
            AD.peek(unit);
        else
            AD.peekRear(unit);
        return unit;
    }

    Units* removeSoldier()
    {
        Units* unit = nullptr;
        AS.dequeue(unit);
        return unit;
    }

    Units* removeMonster(int m) {
        Units* unit = nullptr;
        unit = AM[m];
        AM[m] = AM[AMcount - 1];
        AM[--AMcount] = nullptr;
        return unit;
    }

    Units* removeDrone()
    {
        Units* unit = nullptr;
        if (swapRemove)
        {
            AD.dequeueFront(unit);
            swapRemove = false;
        }
        else
        {
            AD.dequeue(unit);
            swapRemove = true;
        }
        return unit;
    }

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
            if(swapAdd)
            {
                AD.enqueue(X);
                swapAdd = false;
            }
            else
            {
                AD.enqueueFront(X);
                swapAdd = true;
            }
            break;
        }
        return true;
    }
    bool IsEmpty()
    {

    }
    void print()
    {
        cout <<AS.length() << " AS = [";
        AS.printAll();
        cout << "]" << endl;

        cout <<AMcount<< " AM = [";
        cout << AM[0];
        for (int i = 1; i < AMcount; i++)
        {
            cout <<", "<< AM[i] ;
        }
        cout << "]" << endl;

        cout << AD.length() <<" AD = [";
        AD.printAll();
        cout << "]" << endl;

    }
    bool Attack()
    {

    }
    bool GetAttacked()
    {

    }


};

#endif