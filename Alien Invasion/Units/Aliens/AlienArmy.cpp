#include "AlienArmy.h"

bool AlienArmy::addUnit(Units* X)
{
    switch (X->getType())
    {
    case alienSoldier:
        AS.enqueue(X);
        break;
    case alienMonster:
        AM[AMcount++] = X;
        break;
    case alienDrone:
        swapAdd = !swapAdd;
        if (swapAdd)
            AD.enqueue(X);
        else
            AD.enqueueFront(X);
        break;
    }
    return true;
}

bool AlienArmy::peekUnit(unitType type, Units*& unit, int m)
{
    int n;
    switch (type) {
    case alienSoldier:
        return (AS.peek(unit));
    case alienMonster:
        if (!isEmpty(alienMonster))
        {
            unit = AM[m];
            return true;
        }
        return false;
    case alienDrone:
        swapPeek = !swapPeek;
        if (swapPeek)
            return (AD.peekRear(unit));
        return (AD.peek(unit));
    }
}

bool AlienArmy::getUnit(unitType type, Units*& unit, int m)
{
    switch (type) {
    case alienSoldier:
        return (AS.dequeue(unit));
    case alienMonster:
        if (!isEmpty(alienMonster))
        {
            unit = AM[m];
            AM[m] = AM[--AMcount];
            AM[AMcount] = nullptr;
            return true;
        }
        return false;
    case alienDrone:
        swapRemove = !swapRemove;
        if (swapRemove)
            return AD.dequeueRear(unit);
        return AD.dequeue(unit);
    }
}

bool AlienArmy::isEmpty(unitType type)
{
    switch (type) {
    case alienSoldier:
        return AS.isEmpty();
    case alienMonster:
        return !AMcount;
    case alienDrone:
        return AD.isEmpty();
    default:
        return (AS.isEmpty() && !AMcount && AD.isEmpty());
    }
}

void AlienArmy::print()
{
    ///     Print all Alien Soldiers
    cout << AS.length() << " AS [";
    AS.printAll();
    cout << "]\n";

    ///     Print all Alien Monsters
    cout << AMcount << " AM [";
    if (!isEmpty(alienMonster))
    {
        cout << AM[0];
        for (int i = 1; i < AMcount; i++)
        {
            cout << ", " << AM[i];
        }
    }
    cout << "]\n";

    ///     Print all Alien Drones
    cout << AD.length() << " AD [";
    AD.printAll();
    cout << "]\n";
}

bool AlienArmy::fight() {
    return true;
}