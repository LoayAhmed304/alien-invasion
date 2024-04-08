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
        switch (X->getType())
        {
        case earthSoldier:
            ES.enqueue(X);
            break;
        case earthTank:
            ET.push(X);
            break;
        case earthGunnery:
            EG.enqueue(X, (X->getCurHealth() + X->getPower()));
            break;
        }
        return true;
    }

    bool peekUnit(unitType type, Units*& unit)
    {
        int n;
        switch (type) {
        case earthSoldier:
            return (ES.peek(unit));
        case earthTank:
            return ET.peek(unit);
        case earthGunnery:
            return EG.peek(unit, n);
        }
    }

    bool getUnit(unitType type, Units*& unit)
    {
        int n;
        switch (type) {
        case earthSoldier:
            return (ES.dequeue(unit));
        case earthTank:
            return ET.pop(unit);
        case earthGunnery:
            return EG.dequeue(unit, n);
        }
    }

    bool isEmpty(unitType type = earth)
    {
        switch (type) {
        case earthSoldier:
            return ES.isEmpty();
        case earthTank:
            return ET.isEmpty();
        case earthGunnery:
            return EG.isEmpty();
        case earth:
            return (ES.isEmpty() && EG.isEmpty() && ET.isEmpty());
        }
    }

    int length(unitType type)
    {
        switch (type) {
        case earthSoldier:
            return ES.length();
        case earthTank:
            return ET.length();
        case earthGunnery:
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
