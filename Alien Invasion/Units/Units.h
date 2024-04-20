#ifndef UNITS_H
#define UNITS_H

#include <iostream>
using namespace std;
class Game;

enum unitType
{
    earthSoldier,
    earthTank,
    earthGunnery,
    earthHeal,
    alienSoldier,
    alienMonster,
    alienDrone
};

class Units
{
private:
    unitType type;
    int Tj, Ta, Td, Df, Dd, UAP, health, power, attack_cap, cur_health, TimeUML;
    bool InsideUML;
protected:
    int id;
    static int eID;
    static int aID;
    Game* game;
public:
    Units(unitType type, int power, int health, int atk_cap, Game* g);
    virtual bool attack() = 0;
    virtual bool getAttacked(int dmg);
    virtual bool isDead() = 0;
    virtual unitType getType() const;
    virtual int getHealth() const;
    virtual int getCurHealth() const;
    virtual int getPower() const;
    virtual int getAttackCap() const;
    virtual int getHealthPerc()const;

    virtual bool checkUML() const;
    virtual int getUMLtime();
    virtual bool insideUML();
    virtual bool exitUML();
    virtual bool enterUML();


    friend std::ostream& operator<<(std::ostream& os, const Units* obj);
};
#endif