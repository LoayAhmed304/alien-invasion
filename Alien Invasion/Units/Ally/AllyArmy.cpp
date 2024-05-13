#include "AllyArmy.h"

bool AllyArmy::addUnit(Units* X)
{
    switch (X->getType())
    {
    case saverUnit:
        SU.enqueue(X);
        break;
    }
    return true;
}

bool AllyArmy::peekUnit(unitType type, Units*& unit)
{
    switch (type) {
    case saverUnit:
        return (SU.peek(unit));
    }
}

bool AllyArmy::getUnit(unitType type, Units*& unit)
{
    switch (type) {
    case saverUnit:
        return (SU.dequeue(unit));
    }
}

int AllyArmy::getLength(unitType type)
{
    switch (type) {
    case saverUnit:
        return (SU.length());
    }
}

bool AllyArmy::isEmpty(unitType type)
{
    switch (type) {
    case saverUnit:
        return SU.isEmpty();
    case alliedArmy:
        return SU.isEmpty();
    }
}

void AllyArmy::print()
{
    ///     Print all Saver Units
    cout << SU.length() << " SU [";
    SU.printAll();
    cout << "]\n";
}

bool AllyArmy::fight()
{
    bool a = false;
    Units* unit;
    if (peekUnit(saverUnit, unit))
        a = unit->attack();
    return (a);
}

AllyArmy::~AllyArmy()
{
    Units* temp;
    int n;
    while (SU.dequeue(temp))
    {
        delete temp;
        temp = nullptr;
    }
}
