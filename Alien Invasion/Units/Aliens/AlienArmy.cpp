#include "AlienArmy.h"

AlienArmy::AlienArmy(): swap(true), swapPeek(true)
{}

bool AlienArmy::addUnit(Unit* X)
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


bool AlienArmy::peekUnit(unitType type, Unit*& unit)
{
    switch (type) {
    case alienSoldier:
        return AS.peek(unit);
    case alienMonster:
        return AM.peek(unit);
    case alienDrone:
        swapPeek = !swapPeek;
        if (swapPeek)
            return AD.peekRear(unit);
        return AD.peek(unit);
    }
}

bool AlienArmy::getUnit(unitType type, Unit*& unit)
{
    switch (type) {
    case alienSoldier:
        return AS.dequeue(unit);
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
        return AS.length();
    case alienMonster:
        return AM.length();
    case alienDrone:
        return AD.length();
    }
}

bool AlienArmy::isEmpty(unitType type) const
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

void AlienArmy::print() const
{
    /// Print all Alien Soldiers
    cout << AS.length() << " AS [";
    AS.printAll();
    cout << "]\n";

    /// Print all Alien Monsters
    cout << AM.length() << " AM [";
    AM.printAll();
    cout << "]\n";

    /// Print all Alien Drones
    cout << AD.length() << " AD [";
    AD.printAll();
    cout << "]\n";
}

bool AlienArmy::fight()
{
    Unit* unit;
    bool a = false, b = false, c = false, d = false;
   if (peekUnit(alienSoldier, unit))
        a = unit->attack();
    if (peekUnit(alienMonster, unit))
        b = unit->attack();
    if (getLength(alienDrone) > 1)
    {
        peekUnit(alienDrone, unit);
        c = unit->attack();
        peekUnit(alienDrone, unit);
        d = unit->attack();
    }

    return (a || b || c || d);
}

void AlienArmy::updateD(Unit* unit)
{
    totalDf += unit->getDf();
    totalDd += unit->getDd();
    totalDb += unit->getDb();
}

void AlienArmy::returnD(float& f, float& d, float& b) const
{
    f = totalDf;
    d = totalDd;
    b = totalDb;
}

AlienArmy::~AlienArmy()
{
    Unit* temp;
    while (AM.remove(temp))
    {
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
