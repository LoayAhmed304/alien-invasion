#pragma once
#include "Units.h"
#include "Earth_Gunners.h"
#include "Earth_Tanks.h"
#include "Earth_Soldier.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"
#include "../DataStructures/priQueue.h"
using namespace std;
class EarthArmy
{
private:
    LinkedQueue <Earth_Soldier*> ES;
public:
    virtual void dummy() {}
    bool AddUnit(Units* X)
    {
        if (dynamic_cast<Earth_Soldier*>(X))
        {
            ES.enqueue(dynamic_cast<Earth_Soldier*>(X));
        }
        return true;
    }
    void print()
    {
        cout << "ES = ";
        ES.printAll();
    }
};