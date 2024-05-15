#include "AllyArmy.h"

bool AllyArmy::addUnit(Unit* X)
{
    switch (X->getType())
    {
    case saverUnit:
        SU.enqueue(X);
        break;
    default:
        return false;
    }
}

bool AllyArmy::peekUnit(unitType type, Unit*& unit) const
{
    switch (type) {
    case saverUnit:
        return SU.peek(unit);
    default:
        return false;
    }
}

bool AllyArmy::getUnit(unitType type, Unit*& unit)
{
    switch (type) {
    case saverUnit:
        return SU.dequeue(unit);
    default:
        return false;
    }
}

int AllyArmy::getLength(unitType type) const
{
    switch (type) {
    case saverUnit:
        return SU.length();
    default:
        return 0;
    }
}

bool AllyArmy::isEmpty(unitType type) const
{
    switch (type)
    {
    case saverUnit:
        return SU.isEmpty();
    default:
        return false;
    }
}

void AllyArmy::print() const
{
    /// Print all Saver Units
    cout << SU.length() << " SU [";
    SU.printAll();
    cout << "]\n";
}

bool AllyArmy::fight()
{
    bool a = false;
    Unit* unit;
    if (peekUnit(saverUnit, unit))
        a = unit->attack();

    return a;
}

AllyArmy::~AllyArmy()
{
    Unit* temp;
    while (SU.dequeue(temp))
    {
        delete temp;
        temp = nullptr;
    }
}