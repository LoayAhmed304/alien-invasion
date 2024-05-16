#include "EarthArmy.h"

EarthArmy::EarthArmy(): infCount(0), totalInfected(0)
{}

bool EarthArmy::addUnit(Unit* X)
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

bool EarthArmy::peekUnit(unitType type, Unit*& unit) const
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

bool EarthArmy::getUnit(unitType type, Unit*& unit)
{
    switch (type) {
    case earthSoldier:
        return ES.dequeue(unit);
    case earthTank:
        return ET.pop(unit);
    case earthGunnery:
        int n;
        return EG.dequeue(unit, n);
    case earthHeal:
        return EH.pop(unit);
    }
}

int EarthArmy::getLength(unitType type) const
{
    switch (type) {
    case earthSoldier:
        return ES.length();
    case earthTank:
        return ET.length();
    case earthGunnery:
        return EG.length();
    case earthHeal:
        return EH.length();
    }
}

bool EarthArmy::isEmpty(unitType type) const
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

void EarthArmy::print() const
{
    /// Print all Earth Soldiers
    cout << ES.length() << " ES [";
    ES.printAll();
    cout << "]\n";

    /// Print all Earth Tanks
    cout << ET.length() << " ET [";
    ET.printAll();
    cout << "]\n";

    /// Print all Earth Gunneries
    cout << EG.length() << " EG [";
    EG.printAll();
    cout << "]\n";

    /// Print all Earth Heal
    cout << EH.length() << " EH [";
    EH.printAll();
    cout << "]\n";
}

bool EarthArmy::fight()
{
    bool a = false, b = false, c = false;
    Unit* unit;
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

bool EarthArmy::inDanger(int p) const
{
    int totalSoldiers = Unit::getTotalUnits(earthArmy);
    if(totalSoldiers)
        return (infCount * 100 / totalSoldiers) > p;

    return false;
}

bool EarthArmy::getRandomES(Unit*& unit, int index)
{
    Unit* dummyUnit = nullptr;
    Unit* target = nullptr;
    LinkedQueue<Unit*> temp;
    int i = 0;
    while (ES.dequeue(dummyUnit))
    {
        if (i == index)
        {
            if (dummyUnit->isInfected())      // if the unit in the specified random index is already infected, we'll increment the target index by 1
                ++index;                      // what if the random index generated was the last index already?
            else                              // then we'll loop again while enqueuing the templist and take the first not-infected soldier
                target = dummyUnit;
        }
        temp.enqueue(dummyUnit);
        ++i;
    }
    while (temp.dequeue(dummyUnit))
    {
        if (!target)
        {
            if (!dummyUnit->isInfected())
                target = dummyUnit;
        }
        ES.enqueue(dummyUnit);
    }

    unit = target;
    if(unit)
        return true;
    return false;
}

void EarthArmy::updateD(Unit* unit)
{
    totalDd += unit->getDd();
    totalDf += unit->getDf();
    totalDb += unit->getDb();
}

void EarthArmy::updateHealed()
{
    ++totalHealed;
}

int EarthArmy::getHealed() const
{
    return totalHealed;
}

void EarthArmy::returnD(float& f, float& d, float& b) const
{
    f = totalDf;
    d = totalDd;
    b = totalDb;
}

void EarthArmy::incInfected()
{
    ++infCount;
    ++totalInfected;
}

void EarthArmy::decInfected()
{
    if (infCount != 0)
        --infCount;
}

int EarthArmy::getinfCount() const
{
    return infCount;
}

int EarthArmy::getTotalInfected() const
{
    return totalInfected;
}

EarthArmy::~EarthArmy()
{
    Unit* temp;
    int n;
    while (EH.pop(temp))
    {
        delete temp;
        temp = nullptr;
    }
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
