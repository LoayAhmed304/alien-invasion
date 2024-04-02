#pragma once
#include "Units.h"
#include "Alien_Soldier.h"
#include "Alien_Monster.h"
#include "Alien_Drone.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/Deque.h"

class AlienArmy : public Units {
private:
    LinkedQueue <Alien_Soldier> *AS;
    Alien_Monster * AM [1000];
    int AMcount = 0;
    Deque <Alien_Drone> AD;
public:
    bool addUnit()
    {
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