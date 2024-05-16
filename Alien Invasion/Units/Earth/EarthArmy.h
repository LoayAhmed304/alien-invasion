#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../Unit.h"
#include "../../DataStructures/LinkedQueue.h"
#include "../../DataStructures/ArrayStack.h"
#include "../../DataStructures/priQueue.h"

class EarthArmy
{
private:
    LinkedQueue <Unit*> ES;
    ArrayStack <Unit*> ET;
    priQueue <Unit*> EG;
    ArrayStack <Unit*> EH;
    int infCount;
    float totalDf, totalDd, totalDb;		// Total D(f/d/b) for the destructed units (float for the decimal represntation in output file creation)
    int totalHealed;
    int totalInfected;
public:
    EarthArmy();
    bool addUnit(Unit*);
    bool peekUnit(unitType, Unit*&) const;
    bool getUnit(unitType, Unit*&);
    int getLength(unitType) const;
    bool isEmpty(unitType) const;
    void print() const;
    bool fight();        // Peeks each earth unit and calls its attack
    bool inDanger(int) const;
    bool getRandomES(Unit*&, int);

    void updateD(Unit*);
    void updateHealed();
    int getHealed() const;
    void returnD(float&, float&, float&) const;
    void incInfected();
    void decInfected();
    int getinfCount() const;
    int getTotalInfected() const;

    ~EarthArmy();
};
#endif
