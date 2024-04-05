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
    Units * AM [1000];
    int AMcount = 0;
    Deque <Units*> AD;
    bool swap = false;
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
            if(swap)
            {
                AD.enqueue(X);
                swap = false;
            }
            else
            {
                AD.enqueueFront(X);
                swap = true;
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