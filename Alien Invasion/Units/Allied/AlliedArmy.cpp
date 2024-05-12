#include "AlliedArmy.h"

bool AlliedArmy::addUnit(Units* X)
{
    switch (X->getType())
    {
    case saverUnit:
        SU.enqueue(X);
        break;
    }
    return true;
}

bool AlliedArmy::peekUnit(unitType type, Units*& unit)
{
    switch (type) {
    case saverUnit:
        return (SU.peek(unit));
    }
}

bool AlliedArmy::getUnit(unitType type, Units*& unit)
{
    switch (type) {
    case saverUnit:
        return (SU.dequeue(unit));
    }
}

int AlliedArmy::getLength(unitType type)
{
    switch (type) {
    case saverUnit:
        return (SU.length());
    }
}

bool AlliedArmy::isEmpty(unitType type)
{
    switch (type) {
    case saverUnit:
        return SU.isEmpty();
    case alliedArmy:
        return SU.isEmpty();
    }
}

void AlliedArmy::print()
{
    ///     Print all Saver Units
    cout << SU.length() << " SU [";
    SU.printAll();
    cout << "]\n";
}

bool AlliedArmy::fight()
{
    bool a = false;
    Units* unit;
    if (peekUnit(saverUnit, unit))
        a = unit->attack();
    return (a);
}

AlliedArmy::~AlliedArmy()
{
    Units* temp;
    int n;
    while (SU.dequeue(temp))
    {
        delete temp;
        temp = nullptr;
    }
}
