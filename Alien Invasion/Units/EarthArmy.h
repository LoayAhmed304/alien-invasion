#pragma once
#include "Units.h"
#include "EarthGunners.h"
#include "EarthTanks.h"
#include "EarthSoldier.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"
#include "../DataStructures/priQueue.h"
using namespace std;
class EarthArmy
{
private:
    LinkedQueue <EarthSoldier*> ES;
    ArrayStack <EarthTanks*> ET;
    priQueue <EarthGunners*> EG;
public:
    virtual void dummy() {}
    bool AddUnit(Units* X)
    {
        if (dynamic_cast<EarthSoldier*>(X))
        {
            ES.enqueue(dynamic_cast<EarthSoldier*>(X));
        }
        if (dynamic_cast<EarthTanks*>(X))
        {
            ET.push(dynamic_cast<EarthTanks*>(X));
        }
        if (dynamic_cast<EarthGunners*>(X))
        {
            /*EG.enqueue(dynamic_cast<EarthGunners*>(X));*/
        }
        return true;
    }
    void print()
    {
        cout << "ES = ";
        ES.printAll();
        cout << "ET = ";
        ET.printAll();
        cout << "EG = ";
        EG.printAll();

    }
};