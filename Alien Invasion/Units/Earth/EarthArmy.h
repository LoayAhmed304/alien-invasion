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

    bool isEmptyES()
    {
        return ES.isEmpty();
    }

    bool isEmptyET()
    {
        return ET.isEmpty();
    }

    bool isEmptyEG()
    {
        return EG.isEmpty();
    }

    bool isEmpty()
    {
        return (isEmptyES() && isEmptyET() && isEmptyEG());
    }

    int lengthES()
    {
        return ES.length();
    }

    int lengthET()
    {
        return ET.length();
    }

    int lengthEG()
    {
        return EG.length();
    }

    void printES()
    {
        cout << ES.length() << " ES [";
        ES.printAll();
        cout << "]\n";
    }

    void printET()
    {
        cout << ET.length() << " ET [";
        ET.printAll();
        cout << "]\n";
    }

    void printEG()
    {
        cout << EG.length() << " EG [";
        EG.printAll();
        cout << "]\n";
    }

    void print()
    {
        printES();
        printET();
        printEG();
    }
};
#endif