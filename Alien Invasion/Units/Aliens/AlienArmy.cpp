#include "AlienArmy.h"

bool AlienArmy::addUnit(Units* X)
{
    switch (X->getType())
    {
    case alienSoldier:
        AS.enqueue(X);
        break;
    case alienMonster:
        AM.insert(X);
        break;
    case alienDrone:
        swap = !swap;
        if (swap)
            AD.enqueue(X);
        else
            AD.enqueueFront(X);
        break;
    }
    return true;
}

bool AlienArmy::peekUnit(unitType type, Units*& unit)
{
    int n;
    switch (type) {
    case alienSoldier:
        return (AS.peek(unit));
    case alienMonster:
        return AM.peek(unit);
    case alienDrone:
        swapPeek = !swapPeek;
        if (swapPeek)
            return (AD.peekRear(unit));
        return (AD.peek(unit));
    }
}

bool AlienArmy::getUnit(unitType type, Units*& unit)
{
    switch (type) {
    case alienSoldier:
        return (AS.dequeue(unit));
    case alienMonster:
        return AM.remove(unit);
    case alienDrone:
        swap = !swap;
        if (swap)
            return AD.dequeue(unit);
        return AD.dequeueRear(unit);
    }
}

int AlienArmy::getLength(unitType type)
{
    switch (type) {
    case alienSoldier:
        return (AS.length());
    case alienMonster:
        return AM.length();
    case alienDrone:
        return AD.length();
    }
}

bool AlienArmy::isEmpty(unitType type)
{
    switch (type) {
    case alienSoldier:
        return AS.isEmpty();
    case alienMonster:
        return AM.isEmpty();
    case alienDrone:
        return AD.isEmpty();
    case alienArmy:
        return (AS.isEmpty() && AM.isEmpty() && AD.isEmpty());
    }
}

void AlienArmy::print()
{
    ///     Print all Alien Soldiers
    cout << AS.length() << " AS [";
    AS.printAll();
    cout << "]\n";

    ///     Print all Alien Monsters
    cout << AM.length() << " AM [";
    AM.printAll();
    cout << "]\n";

    ///     Print all Alien Drones
    cout << AD.length() << " AD [";
    AD.printAll();
    cout << "]\n";
}

bool AlienArmy::fight()
{
    Units* unit;
    bool a = false, b = false, c = false;
   if (peekUnit(alienSoldier, unit))
        unit->attack();
    if (peekUnit(alienMonster, unit))
        unit->attack();
    if (getLength(alienDrone) > 1)
    {
        peekUnit(alienDrone, unit);
        unit->attack();
        peekUnit(alienDrone, unit);
        unit->attack();
    }

    return (a || b || c);
}

AlienArmy::~AlienArmy()
{
    Units* temp;
    for (int i = 0; !AM.isEmpty(); ++i)
    {
        AM.remove(temp);
        delete temp;
        temp = nullptr;
    }
    while (AS.dequeue(temp))
    {
        delete temp;
        temp = nullptr;
    }
    while (AD.dequeue(temp))
    {
        delete temp;
        temp = nullptr;
    }
}
