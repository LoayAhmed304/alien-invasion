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
    case earthArmy:
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
    bool a = false, b = false, c = false;
    Units* unit;
    if (peekUnit(earthSoldier, unit))
        a = unit->attack();
    if (peekUnit(earthTank, unit))
        b = unit->attack();
    if (peekUnit(earthGunnery, unit))
        c = unit->attack();
    if (peekUnit(earthHeal, unit))
        unit->attack();
    return (a || b || c);
}

int EarthArmy::inDanger()
{
    if(Units::getTotalUnits(earthArmy))
    return (infCount * 100 / Units::getTotalUnits(earthArmy));
    return 0;
}

void EarthArmy::incInfected()
{
    infCount++;
}
void EarthArmy::decInfected()
{
    infCount--;
    if (infCount <= 0)
        infCount = 0;
}
int EarthArmy::getinfCount()
{
    return infCount;
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
