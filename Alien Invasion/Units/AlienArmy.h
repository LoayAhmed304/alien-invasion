#pragma once
#include "Units.h"
#include "AlienSoldier.h"
#include "AlienMonster.h"
#include "AlienDrone.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/Deque.h"

class AlienArmy : public Units {
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
            AM[AMcount] = dynamic_cast<AlienMonster*>(X);
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

    }
    bool Attack()
    {

    }
    bool GetAttacked()
    {

    }
    virtual bool IsDead() = 0;

};