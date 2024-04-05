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
    LinkedQueue <Units*> ES;
    ArrayStack <Units*> ET;
    priQueue <Units*> EG;
public:
    virtual void dummy() {}
    bool AddUnit(Units* X)
    {
        switch (X->getType()[1])
        {
        case 'S':
            ES.enqueue(X);
            break;
        case 'T':
            ET.push(X);
            break;
        case 'G':
            EG.enqueue(X, (X->getCurHealth() + X->getPower()));
            break;
        }
        return true;

    }
    void print()
    {
        cout << ES.length() << " ES = [";
        ES.printAll();
        cout << "]" << endl;

        cout << ET.length() << " ET = [";
        ET.printAll();
        cout << "]" << endl;

        cout << EG.length() << " EG = [";
        EG.printAll();
        cout << "]" << endl;


    }
};