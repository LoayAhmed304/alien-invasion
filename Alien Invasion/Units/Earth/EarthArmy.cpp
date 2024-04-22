#include "EarthArmy.h"

bool EarthArmy::addUnit(Units* X)
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
    case earthHeal:
        EH.push(X);
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
    case earthHeal:
        return EH.peek(unit);
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
    case earthHeal:
        return EH.pop(unit);
    }
}

int EarthArmy::getLength(unitType type)
{
    switch (type) {
    case earthSoldier:
        return (ES.length());
    case earthTank:
        return ET.length();
    case earthGunnery:
        int n;
        return EG.length();
    case earthHeal:
        return EH.length();
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
    case earthHeal:
        return EH.isEmpty();
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

    ///     Print all Earth Heal
    cout << EH.length() << " EH [";
    EH.printAll();
    cout << "]\n";
}

bool EarthArmy::fight()
{
    Units* unit;
    /*if (peekUnit(earthSoldier, unit))
        unit->attack();*/
    if (peekUnit(earthTank, unit))
        unit->attack();
    if (peekUnit(earthGunnery, unit))
        unit->attack();
    if (peekUnit(earthHeal, unit))
        unit->attack();
    return true;
}

EarthArmy::~EarthArmy()
{
    Units* temp;
    int n;
    while (ES.dequeue(temp))
    {
        delete temp;
        temp = nullptr;
    }
    while (EG.dequeue(temp, n))
    {
        delete temp;
        temp = nullptr;
    }
    while (ET.pop(temp))
    {
        delete temp;
        temp = nullptr;
    }
}
