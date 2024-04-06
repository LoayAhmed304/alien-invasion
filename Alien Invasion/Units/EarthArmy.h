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
    Units* getSoldier()
    {
        Units* temp= nullptr;
        (ES.peek(temp));
        return temp;
    }

    Units* getTank()
    {
        Units* temp = nullptr;
        ET.peek(temp);
        return temp;
    }

    Units* getGunnery()
    {
        Units* temp= nullptr;
        int n;
        EG.peek(temp, n);
        return temp;
    }

    Units* removeSoldier()
    {
        Units* temp = nullptr;
        ES.dequeue(temp);
        return(temp);
    }

    Units* removeTank()
    {
        Units* temp = nullptr;
        ET.pop(temp);
        return temp;
    }

    Units* removeGunnery()
    {
        int n;
        Units* temp = nullptr;
        EG.dequeue(temp, n);
        return temp;
    }

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