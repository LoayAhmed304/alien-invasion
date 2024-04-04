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
    LinkedQueue <AlienSoldier*> AS;
    AlienMonster * AM [1000];
    int AMcount = 0;
    Deque <AlienDrone*> AD;
public:
    bool addUnit(Units* X)
    {
        if (dynamic_cast<AlienSoldier*>(X))
        {
            AS.enqueue(dynamic_cast<AlienSoldier*>(X));
        }
        if (dynamic_cast<AlienMonster*>(X))
        {
            AM[AMcount++] = dynamic_cast<AlienMonster*>(X);
        }
        if (dynamic_cast<AlienDrone*>(X))
        {
            AD.enqueue(dynamic_cast<AlienDrone*>(X));
        }
        return true;
    }
    bool IsEmpty()
    {

    }
    void print()
    {
        cout << "AS = " << endl;
        AS.printAll();
        cout << "AM = " << endl;
        for (int i = 0; i < AMcount; i++)
        {
            cout << AM[i] << endl;
        }
        cout << "AD = " << endl;
        AD.printAll();

    }
    bool Attack()
    {

    }
    bool GetAttacked()
    {

    }


};

#endif