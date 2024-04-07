#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../Units.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/ArrayStack.h"
#include "../../DataStructures/priQueue.h"
using namespace std;
class EarthArmy
{
private:
    LinkedQueue <Units*> ES;
    ArrayStack <Units*> ET;
    priQueue <Units*> EG;
public:
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

    bool peekSoldier(Units*& unit)
    {
        unit->getType();
        return (ES.peek(unit));
    }

    bool peekTank(Units*& unit)
    {
        return (ET.peek(unit));
    }

    bool peekGunnery(Units*& unit)
    {
        int n;
        return (EG.peek(unit, n));
    }

    bool removeSoldier(Units*& unit)
    {
        return (ES.dequeue(unit));
    }

    bool removeTank(Units*& unit)
    {
        return (ET.pop(unit));
    }

    bool removeGunnery(Units*& unit)
    {
        int n;
        return (EG.dequeue(unit, n));
    }

    bool isEmpty(char s = 'A')
    {
        switch (s) {
        case 'S':
            return ES.isEmpty();
        case 'G':
            return EG.isEmpty();
        case 'T':
            return ET.isEmpty();
        default:
            return (ES.isEmpty() && EG.isEmpty() && ET.isEmpty());
        }
    }


    int length(char e)
    {
        switch (e) {
        case 'S':
            return ES.length();
        case 'T':
            return ET.length();
        case 'G':
            return EG.length();
        }
    }

    void print()
    {
        ///     Print all Earth Soldiers
        cout << ES.length() << " ES [";
        ES.printAll();
        cout << "]\n";
        ///     Print all Earth Tanks
        cout << ET.length() << " ET [";
        ET.printAll();
        cout << "]\n";
        ///     Print all Earth Gunneries
        cout << EG.length() << " EG [";
        EG.printAll();
        cout << "]\n";
    }
};
#endif