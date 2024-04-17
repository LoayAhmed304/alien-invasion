#include "EarthArmy.h"

bool EarthArmy::AddUnit(Units* X)
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

bool EarthArmy::peekUnit(unitType type, Units*& unit)
{
    switch (type) {
    case earthSoldier:
        return (ES.peek(unit));
    case earthTank:
        return ET.peek(unit);
    case earthGunnery:
        int n;
        return EG.peek(unit, n);
    }
}

bool EarthArmy::getUnit(unitType type, Units*& unit)
{
    switch (type) {
    case earthSoldier:
        return (ES.dequeue(unit));
    case earthTank:
        return ET.pop(unit);
    case earthGunnery:
        int n;
        return EG.dequeue(unit, n);
    }
}

bool EarthArmy::isEmpty(unitType type)
{
    switch (type) {
    case earthSoldier:
        return ES.isEmpty();
    case earthTank:
        return ET.isEmpty();
    case earthGunnery:
        return EG.isEmpty();
    default:
        return (ES.isEmpty() && EG.isEmpty() && ET.isEmpty());
    }
}

void EarthArmy::print()
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

bool EarthArmy::fight()
{
    return false;
}
